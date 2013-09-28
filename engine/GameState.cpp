#include <engine/mesh/core.h>
#include "GameState.h"

GameState::GameState()
{
    last_frame = 0;
    last_frame_time = 1;
	shouldQuit = false;
}