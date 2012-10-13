#pragma once

//C99 functions
#define isnan _isnan
#define isinf _isinf

//crossplatform constants
#ifdef _DEBUG
    #define DEBUG
#endif

#ifdef _WIN64
	#define DOUBLE_PRECISION
#endif