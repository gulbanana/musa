#include <algorithm>
#include "Rect4F.h"
using namespace std;

Rect4F Rect4F::unify(Rect4F a, Rect4F b)
{
	return Rect4F(max(a.x1,b.x1), max(a.y1,b.y1), max(a.x2,b.x2), max(a.y2,b.y2));
}