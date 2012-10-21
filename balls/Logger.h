#pragma once
#include <string>
#include <fstream>
#include <memory>

class Logger
{
	static std::unique_ptr<std::ofstream> _file;
public:
	static void init();
	static void log(std::string data);
};

