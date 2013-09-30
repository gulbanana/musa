#include <tile/stdafx.h>
#include <SDL_opengl.h>
#include "GLBlitSystem.h"
using namespace std;

vector<ISystem::ID> GLBlitSystem::required_systems() const
{
	return require();
}

GLBlitSystem::GLBlitSystem(unsigned int pixelWidth, unsigned int pixelHeight) : 
	_tram(1, 1), _surface(nullptr), _fonts(nullptr), _width(pixelWidth), _height(pixelHeight), _current_font(0), _current_size(24)
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

	//load grid
	resize();
}

GLBlitSystem::~GLBlitSystem(void)
{
	delete _fonts;
	SDL_FreeSurface(_surface);
}

void GLBlitSystem::on_wake()
{
	glClear(GL_COLOR_BUFFER_BIT);
	auto metrics = _fonts->get_vertical_metrics(_current_font, _current_size);
	
	float pixelY = metrics.ascender;
	for (unsigned int j = 0; j < _tram.height; j++)
	{
		float pixelX = 0;
		for (unsigned int i = 0; i < _tram.width; i++)
		{
			auto t = _tram.buffer[_tram.width*j+i];
			glColor4f(t.shade.r, t.shade.g, t.shade.b, t.shade.a);
			
			_fonts->begin_draw();	//constantly flushing the text buffer is slow, but required to get colours correct for now
			pixelX = _fonts->draw_character(_current_font, _current_size, pixelX, pixelY, t.value);
			_fonts->end_draw();
		}

		pixelY += metrics.line_height;
	}

	SDL_GL_SwapBuffers();
}

bool GLBlitSystem::on_event(SDL_Event& event)
{
	if (event.type == SDL_VIDEORESIZE)
	{
		_width = event.resize.w;
		_height = event.resize.h;
		resize();
	}
	
	return false;
}

grid* GLBlitSystem::get_tram()
{
	return &_tram;
}

void GLBlitSystem::resize()
{
    //might be able to avoid this with sdl 2.0..
    if (_surface != nullptr) SDL_FreeSurface(_surface);
	_surface = SDL_SetVideoMode(_width, _height, 32, SDL_OPENGL | SDL_RESIZABLE);
	if (_surface == nullptr) throw std::runtime_error("failed to init gl context");
    
	//GL init
	glEnable(GL_BLEND);							//rgba translucency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.f, 0.f, 0.f, 0.f);			//black background
	glDisable(GL_TEXTURE_2D);					//just text
	glDisable(GL_DEPTH_TEST);
    
	//setup world-space
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//setup device-space
	glViewport(0, 0, _width, _height);

	//setup clipping-space 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, _width, 0, _height, -1, 1);

    //load fonts - this must be done for every gl init :(
	if (_fonts != nullptr) delete _fonts;
	_fonts = new FontManager(512, 512);
	if (!_fonts->add_font(0, "consola.ttf")) throw std::runtime_error("failed to add font");
	if (!_fonts->add_font(1, "consolai.ttf")) throw std::runtime_error("failed to add font");
	if (!_fonts->add_font(2, "consolab.ttf")) throw std::runtime_error("failed to add font");
    
	//this will only work for a fixedwidth font
	auto vMetrics = _fonts->get_vertical_metrics(_current_font, _current_size);
	auto hMetrics = _fonts->get_horizontal_metrics(_current_font, _current_size, '@');	
	_tram.resize(_width/hMetrics.glyph_width, _height/vMetrics.line_height);
}