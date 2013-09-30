#include <tile/stdafx.h>
#include "CTransform.h"

namespace std
{
	string to_string(CTransform t)
	{
		return string("Transform{") 
			+ "translate: " + to_string(t.translate) + ","
			+ "rotate: " + to_string(t.rotate) 
		+ "}";
	}
}