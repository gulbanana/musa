#include <tile/stdafx.h>
#include <SDL_opengl.h>
#include "GLBlitSystem.h"
using namespace std;

#define FONT_SIZE 24

vector<ISystem::ID> GLBlitSystem::required_systems() const
{
	return require();
}

GLBlitSystem::GLBlitSystem(unsigned int pixelWidth, unsigned int pixelHeight) : _tram(pixelWidth/FONT_SIZE, pixelHeight/FONT_SIZE), _surface(nullptr)
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

    //might be able to avoid this with sdl 2.0..
    if (_surface != nullptr) SDL_FreeSurface(_surface);
	_surface = SDL_SetVideoMode(pixelWidth, pixelHeight, 32, SDL_OPENGL | SDL_RESIZABLE);
	if (_surface == nullptr) throw std::runtime_error("failed to init gl context");
    
	//GL init
	glEnable(GL_BLEND);							//rgba translucency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glClearColor(0.f, 0.f, 0.f, 0.f);			//black background
	glDisable(GL_TEXTURE_2D);					//just text
	glDisable(GL_DEPTH_TEST);

	//setup device-space
	glViewport(0, 0, pixelWidth, pixelHeight);

	//setup world-space
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	//setup clipping-space 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, pixelWidth, 0, pixelHeight, -1, 1);

	//load fonts
	_fonts = sth_create(512,512);
	if (!_fonts) throw std::runtime_error("failed to init font stash");
	if (!sth_add_font(_fonts, 0, "consola.ttf")) throw std::runtime_error("failed to add font");
	if (!sth_add_font(_fonts, 1, "consolai.ttf")) throw std::runtime_error("failed to add font");
	if (!sth_add_font(_fonts, 2, "consolab.ttf")) throw std::runtime_error("failed to add font");
}

GLBlitSystem::~GLBlitSystem(void)
{
	SDL_FreeSurface(_surface);
}

void GLBlitSystem::on_wake()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4ub(255,255,255,255);
		
	sth_begin_draw(_fonts);

	float linestart = 0;
	for (unsigned int j = 0; j < _tram.height; j++)
	{
		float lineheight = 0;
		float charstart = 0;
		for (unsigned int i = 0; i < _tram.width; i++)
		{
			sth_draw_text(_fonts, 0, FONT_SIZE, charstart, linestart, ".", &charstart);
		}
		sth_vmetrics(_fonts, 0, FONT_SIZE, NULL,NULL, &lineheight);
		linestart += lineheight;
	}

	float sx,sy,dx,dy,lh;
	static float offset = 0.f;
	
	sx = 100 + offset; sy = 250 + offset;
	offset += 1;

	dx = sx; dy = sy;
	sth_draw_text(_fonts, 0,24.0f, dx,dy,"The quick ",&dx);
	sth_draw_text(_fonts, 1,48.0f, dx,dy,"brown ",&dx);
	sth_draw_text(_fonts, 0,24.0f, dx,dy,"fox ",&dx);
	sth_vmetrics(_fonts, 1,24, NULL,NULL,&lh);
	dx = sx;
	dy -= lh*1.2f;
	sth_draw_text(_fonts, 1,24.0f, dx,dy,"jumps over ",&dx);
	sth_draw_text(_fonts, 2,24.0f, dx,dy,"the lazy ",&dx);
	sth_draw_text(_fonts, 0,24.0f, dx,dy,"dog.",&dx);
	dx = sx;
	dy -= lh*1.2f;
	sth_draw_text(_fonts, 0,12.0f, dx,dy,"Now is the time for all good men to come to the aid of the party.",&dx);
	sth_vmetrics(_fonts, 1,12, NULL,NULL,&lh);
	dx = sx;
	dy -= lh*1.2f*2;
	sth_draw_text(_fonts, 1,18.0f, dx,dy,"Ég get etið gler án þess að meiða mig.",&dx);
	sth_vmetrics(_fonts, 1,18, NULL,NULL,&lh);
	dx = sx;
	dy -= lh*1.2f;

	sth_end_draw(_fonts);
		
	SDL_GL_SwapBuffers();
}

bool GLBlitSystem::on_event(SDL_Event& event)
{
	//if (event.type == SDL_VIDEORESIZE)
		//_renderer->set_viewport(event.resize.w, event.resize.h);
	
	return false;
}

grid* GLBlitSystem::get_tram()
{
	return &_tram;
}