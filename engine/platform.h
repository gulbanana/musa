#pragma once

#ifdef _WIN32
    #define isnan _isnan
	#define setenv(var,val,flag) _putenv(var##"="##val)
#endif