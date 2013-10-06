#pragma once
#include "framework.h"

class GameState
{
public:
    //metrics
	milliseconds last_frame;
    milliseconds last_frame_time;
    
    //control
	bool shouldQuit;

	GameState();
};

