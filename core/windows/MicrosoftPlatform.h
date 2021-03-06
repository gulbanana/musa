#pragma once
#include <core/sdl/SDLPlatformBase.h>

class MicrosoftPlatform : public SDLPlatformBase
{
private:
	milliseconds _tick_offset;

public:
	MicrosoftPlatform();
	~MicrosoftPlatform();

    std::string get_environment_variable(std::string variable) final;
	void set_environment_variable(std::string variable, std::string value) final;

    void println(std::string output) final;

	milliseconds get_ticks() final;
	void sleep_ticks(milliseconds) final;

	FILE* fopen(std::string path, std::string mode) final;
};