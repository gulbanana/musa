#include <core/stdafx.h>
#include "MicrosoftPlatform.h"
#include "Windows.h"

IPlatform* platform;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	platform = new MicrosoftPlatform();

    int status = _main(__argc, __argv);

	delete platform;
	return status;
}