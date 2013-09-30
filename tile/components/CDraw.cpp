#include <tile/stdafx.h>
#include "CDraw.h"

namespace std
{
	string to_string(CDraw d)
	{
		return string("Draw{") 
			+ "layout: " + to_string(d.layout)
		+ "}";
	}
}