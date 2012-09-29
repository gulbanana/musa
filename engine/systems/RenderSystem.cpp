#include <array>
#include <iterator>
#include <typeinfo>
#include "SDL.h"
#include <SDL_opengl.h>
#include "../components.h"
#include "RenderSystem.h"
using namespace std;

vector<IComponent::ID> RenderSystem::required_components()
{
	array<IComponent::ID,2> compTypes = {IComponent::ID::Position2D, IComponent::ID::Geometry2D};
	return vector<IComponent::ID>(compTypes.begin(), compTypes.end());
}

RenderSystem::RenderSystem(int width, int height)
{
	//init and set capabilities
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//specify window coordinates
	glViewport(0, 0, width, height);

	//set background colour
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//create orthogonal projection matrix - device coordinates
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.f, width, height, 0.f, -1.f, 1.f);

	//reset to standard matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

RenderSystem::~RenderSystem()
{
	//gldestroy??
}

bool RenderSystem::on_event(SDL_Event& event)
{
	//gl reset size or something
	return false;
}

void RenderSystem::on_frame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderSystem::on_post_frame()
{
	SDL_GL_SwapBuffers();
}

void RenderSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = entity->get_component<CPosition2D>();
	auto geometry = entity->get_component<CGeometry2D>();

	//glmatrix stuff based on position
	glPushMatrix();
	glTranslatef(position->location.x, position->location.y, 0.f);
	glRotatef(position->orientation, 0.f, 0.f, 1.f);

	glColor4f(geometry->color.red, geometry->color.green, geometry->color.blue, geometry->color.alpha);
	for (auto& poly : geometry->polys)
	{
		poly->draw();
	}

	if (entity->has_component<CLabel>())
	{
		auto label = entity->get_component<CLabel>();
		//gltext?
		//guess i have to signal the ui system here, so maybe this should not be the label processor
	}

	glPopMatrix();
}