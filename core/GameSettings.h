#pragma once

struct GameSettings
{
	std::string window_title;

	int initial_width;
	int initial_height;

	GameSettings(std::string title, int width, int height) 
		: window_title(title), initial_width(width), initial_height(height)
	{}
};