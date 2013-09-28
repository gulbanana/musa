#pragma once
#include <string>

enum class GraphicsMode
{
	MESH_2D,
	MESH_3D,
	TILE
};

struct Settings
{
	std::string window_title;

	int initial_width;
	int initial_height;

	GraphicsMode mode;

	Settings(std::string title, int width, int height, GraphicsMode mode) 
		: window_title(title), initial_width(width), initial_height(height), mode(mode)
	{}
};