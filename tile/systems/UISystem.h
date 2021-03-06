#pragma once
#include <core/framework.h>
#include <core/GameState.h>
#include "IBlitter.h"

#define FPS_SAMPLE_PERIOD 60

class UISystem : public Identified<UISystem,ISystem>
{
private:
    GameState* _state;
    IBlitter* _blitter;

    int fps_samples[FPS_SAMPLE_PERIOD];
    int fps_sample_index;
    float fps_moving_average;
	
	void on_frame() override;

    void measure_fps();

public:
    std::string description() const final;
    std::vector<ISystem::ID> required_systems() const override;
	UISystem(GameState*, IBlitter*);
    ~UISystem();
};

