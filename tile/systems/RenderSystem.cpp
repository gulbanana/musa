#include <tile/stdafx.h>
#include "RenderSystem.h"
#include <algorithm>
using namespace std;

vector<ISystem::ID> RenderSystem::required_systems() const
{
	return require();
}

RenderSystem::RenderSystem(IBlitter* blitter, shared_ptr<GameState> state) : _blitter(blitter), _state(state) {}

RenderSystem::~RenderSystem() {}

int moving_average[5];
int current_fps = 0;
void RenderSystem::on_wake()
{
	auto tram = _blitter->get_tram();

	tram->fill(tile('.'));
	tram->draw(tile('@', colour::RED), 35, 12);
	
	auto fps = 1000/max(_state->last_frame_time,(milliseconds)1);
	if (fps != 1000)
	{
		moving_average[current_fps++] = fps;
		if (current_fps > 4) current_fps = 0;
		auto average_fps = (moving_average[0] + moving_average[1] + moving_average[2] + moving_average[3] + moving_average[4]) / 5;
		tram->draw(string("FPS: ") + to_string(average_fps), 1, 1);
	}
}