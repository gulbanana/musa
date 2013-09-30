#pragma once
#include <core/framework.h>
#include <core/GameState.h>
#include "IBlitter.h"

#define FPS_SAMPLE_PERIOD 60

class UISystem : public Identified<UISystem,ISystem,ThreadedSystemBase>
{
private:
    IBlitter* _blitter;
	std::shared_ptr<GameState> _state;

    int fps_samples[FPS_SAMPLE_PERIOD];
    int fps_sample_index;
    float fps_moving_average;

	std::vector<ISystem::ID> required_systems() const override;
	void on_wake() override;

    void measure_fps();

public:
	UISystem(IBlitter*, std::shared_ptr<GameState>);
    ~UISystem();
};

