#pragma once
class GameState
{
public:
    //metrics
	unsigned last_frame;
    unsigned last_frame_time;
    
    //control
	bool shouldQuit;

	GameState();
};

