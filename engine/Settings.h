#pragma once
#include <string>

enum class GraphicsMode
{
	TWO_D,
	THREE_D
};

struct Settings
{
	std::string window_title;

	int initial_width;
	int initial_height;

	GraphicsMode mode;

	Settings(std::string title, int width, int height) 
		: window_title(title), initial_width(width), initial_height(height), mode(GraphicsMode::TWO_D)
	{}
};