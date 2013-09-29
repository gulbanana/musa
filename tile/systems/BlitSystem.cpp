#include <tile/stdafx.h>
#include <SDL_opengl.h>
#include "BlitSystem.h"
using namespace std;

vector<ISystem::ID> BlitSystem::required_systems() const
{
	return require();
}

BlitSystem::BlitSystem(unsigned int pixelWidth, unsigned int pixelHeight) : _tram(1, 1), _surface(nullptr)
{
	//SDL init
	int rc;
	rc = SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if (rc != 0) throw runtime_error("failed to init doublebuffering");
	rc = SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); 
	if (rc != 0) throw runtime_error("failed to init multisampling");
	rc = SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	if (rc != 0) throw runtime_error("failed to init multisampling");
	rc = SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); 
	if (rc != 0) throw runtime_error("failed to init depth buffer");

    //might be able to avoid this with sdl 2.0..
    if (_surface != nullptr) SDL_FreeSurface(_surface);
	_surface = SDL_SetVideoMode(pixelWidth, pixelHeight, 32, SDL_OPENGL | SDL_RESIZABLE);
	if (_surface == nullptr) throw std::runtime_error("failed to init gl context");
    
	//GL init
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//rgba translucency
	glClearColor(0.f, 0.f, 0.f, 0.f);	//black background

	//setup device-space
	glViewport(0, 0, pixelWidth, pixelHeight);

	//setup world-space
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	//setup clipping-space 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

}

BlitSystem::~BlitSystem(void)
{
	SDL_FreeSurface(_surface);
}

void BlitSystem::on_wake()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapBuffers();
}

bool BlitSystem::on_event(SDL_Event& event)
{
	//if (event.type == SDL_VIDEORESIZE)
		//_renderer->set_viewport(event.resize.w, event.resize.h);
	
	return false;
}
