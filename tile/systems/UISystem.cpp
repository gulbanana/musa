#include "tile/stdafx.h"
#include "UISystem.h"
#include "RenderSystem.h"
using namespace std;

vector<ISystem::ID> UISystem::required_systems() const
{
    return require<RenderSystem>();
}

UISystem::UISystem(GameState* state, IBlitter* blitter) : _state(state), _blitter(blitter) 
{
    memset(&fps_samples, 0, sizeof(fps_samples));
    fps_sample_index = 0;
    fps_moving_average = 0.f;
}

UISystem::~UISystem() {}


void UISystem::on_wake()
{
    measure_fps();
}

void UISystem::measure_fps()
{
    auto tram = _blitter->get_tram();
    auto current_sample = 1000/max(_state->last_frame_time,(milliseconds)1);

	if (current_sample != 1000)
	{
        //rotate sample
		auto previous_sample = fps_samples[fps_sample_index];
        fps_samples[fps_sample_index++] = current_sample;
		if (fps_sample_index == FPS_SAMPLE_PERIOD) fps_sample_index = 0;

        //accumulate average
        fps_moving_average -= (float)previous_sample / (float)FPS_SAMPLE_PERIOD;
        fps_moving_average += (float)current_sample / (float)FPS_SAMPLE_PERIOD;
	}

    tram->draw(string("FPS: ") + to_string((int)fps_moving_average), 1, tram->height-2, colour::RED, font_weight::BOLD);
}