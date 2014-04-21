#include <tile/stdafx.h>
#include <algorithm>
#include <SDL_opengl.h>
#include "GLBlitSystem.h"
#include "UISystem.h"
#include "RenderSystem.h"
using namespace std;

vector<ISystem::ID> GLBlitSystem::required_systems() const
{
	return require<RenderSystem,UISystem>();
}

GLBlitSystem::GLBlitSystem(SDL_Window* window) : _tram(1, 1), _window(window), _fonts(nullptr), _context(nullptr), _font_size(DEFAULT_FONT)
{
	//SDL init
	int rc;
	rc = SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if (rc != 0) throw runtime_error("failed to init doublebuffering");
	rc = SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); 
	if (rc != 0) throw runtime_error("failed to init multisampling");
	rc = SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	if (rc != 0) throw runtime_error("failed to init multisampling");
	rc = SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); 
	if (rc != 0) throw runtime_error("failed to init depth buffer");
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GetWindowSize(_window, &_width, &_height);

	//GL init
    _context = SDL_GL_CreateContext(_window);
    glEnable(GL_BLEND);							//rgba translucency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.f, 0.f, 0.f, 0.f);			//black background
	glDisable(GL_TEXTURE_2D);					//just text
	glDisable(GL_DEPTH_TEST);
    
    //TTF init
	_fonts = new FontManager(512, 512);
	if (!_fonts->load_font(font_weight::REGULAR,     "data/font/regular.ttf")) throw std::runtime_error("failed to load regular font");
	if (!_fonts->load_font(font_weight::BOLD,        "data/font/bold.ttf")) throw std::runtime_error("failed to load bold font");
	if (!_fonts->load_font(font_weight::ITALIC,      "data/font/italic.ttf")) throw std::runtime_error("failed to load italic font");
	if (!_fonts->load_font(font_weight::BOLD_ITALIC, "data/font/bolditalic.ttf")) throw std::runtime_error("failed to load bold-italic font");

    //load grid
    _is_fullscreen = false;
	resizeGrid(RoundingMode::HALF);
}

GLBlitSystem::~GLBlitSystem(void)
{
    SDL_GL_DeleteContext(_context);
	delete _fonts;
}

//called at startup and whenever the font size or screen size changes
void GLBlitSystem::resizeGrid(RoundingMode mode)
{   
	//algorithm to make the screen size 'perfect'. might not work so well if fullscreen
    //step 1: estimate pixel cost
	auto vPixelEstimate = _fonts->get_vertical_metrics(font_weight::REGULAR, _font_size).line_height;
	auto hPixelEstimate = _fonts->get_text_dimensions(font_weight::REGULAR, _font_size, "@@@").maxX/3.f;

    //step 2: determine grid size 
    int hChars, vChars;
    switch (mode)
    {
    case RoundingMode::UP:
        hChars = roundUp((dist)_width / hPixelEstimate);
        vChars = roundUp((dist)_height / vPixelEstimate);
        break;
    case RoundingMode::DOWN:
        hChars = roundDown((dist)_width / hPixelEstimate);
        vChars = roundDown((dist)_height / vPixelEstimate);        
        break;
    case RoundingMode::HALF:
        hChars = roundHalf((dist)_width / hPixelEstimate);
        vChars = roundHalf((dist)_height / vPixelEstimate);        
        break;
    }

    //step 3: calculate actual pixel cost using a faux grid
    float hPixels, vPixels = vPixelEstimate * vChars;
    switch (mode)
    {
    case RoundingMode::UP:
        for (; (hPixels = _fonts->get_text_dimensions(font_weight::REGULAR, _font_size, string(hChars, '@')).maxX) < _width; hChars++);
        break;
    case RoundingMode::DOWN:
        for (; (hPixels = _fonts->get_text_dimensions(font_weight::REGULAR, _font_size, string(hChars, '@')).maxX) > _width; hChars--);
        break;
    case RoundingMode::HALF:
        hPixels = _fonts->get_text_dimensions(font_weight::REGULAR, _font_size, string(hChars, '@').c_str()).maxX;
        break;
    }    

    //step 4: resize the real grid and the viewport
	_tram.resize(hChars, vChars);
    if (_is_fullscreen)
    {
        //set up an offset for the camera, since we can't actually change the screen size
        //XXX no way to go fullscreen yet so it doesn't matter
    } 
    else 
    {
        SDL_SetWindowSize(_window, (int)hPixels, (int)vPixels);
    }
}

//take care of keeping the window surface updated
bool GLBlitSystem::on_event(SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_WINDOWEVENT:
        {
            switch(event.window.event)
            {
                //internal size tracking
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                {
                    _width = event.window.data1;
                    _height = event.window.data2;

                    //setup world-space
	                glMatrixMode(GL_MODELVIEW);
	                glLoadIdentity();

	                //setup device-space
	                glViewport(0, 0, _width, _height);

	                //setup clipping-space 
	                glMatrixMode(GL_PROJECTION);
	                glLoadIdentity();
	                glOrtho(0, _width, 0, _height, -1, 1);

                    return true;
                }

                //externally-initiated resize
                case SDL_WINDOWEVENT_RESIZED:
                {
                    resizeGrid(RoundingMode::HALF);
                    return true;
                }

                //XXX these events don't seem to be occurring
                //case SDL_WINDOWEVENT_MAXIMIZED:
                //{
                //    _is_fullscreen = true;
                //    return true;
                //}
                //case SDL_WINDOWEVENT_RESTORED:
                //{
                //    _is_fullscreen = false;
                //    return true;
                //}

            }
            break;
        }

        case SDL_MOUSEWHEEL:
        {
            auto oldSize = _font_size;
            auto newSize = _font_size + event.wheel.y * 0.5f;
            _font_size = max(min(newSize, MAX_FONT), MIN_FONT);

            resizeGrid((newSize > oldSize) ? RoundingMode::UP : RoundingMode::DOWN);
            break;
        }
    }
	
	return false;
}

//provide a tile-ram buffer for the renderer to draw into
grid* GLBlitSystem::get_tram()
{
	return &_tram;
}

//do blitting
void GLBlitSystem::on_wake()
{
	glClear(GL_COLOR_BUFFER_BIT);
	auto metrics = _fonts->get_vertical_metrics(font_weight::REGULAR, _font_size);
	
	float pixelY = -metrics.descender;
	for (unsigned int j = 0; j < _tram.height; j++)
	{
		float pixelX = 0;
		for (unsigned int i = 0; i < _tram.width; i++)
		{
			auto t = _tram.buffer[_tram.width*j+i];
			glColor4f(t.shade.r, t.shade.g, t.shade.b, t.shade.a);
			
			_fonts->begin_draw();	//constantly flushing the text buffer is slow, but required to get colours correct for now
			pixelX = _fonts->draw_character(t.style, _font_size, pixelX, pixelY, t.value);
			_fonts->end_draw();
		}

		pixelY += metrics.line_height;
	}

	SDL_GL_SwapWindow(_window);
}