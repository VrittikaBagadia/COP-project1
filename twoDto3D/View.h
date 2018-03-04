// View.h
#include "Edg.h"
#include "Vert.h"
class View
{
private:
	const int nop, noe; //no of points
	Vert v[nop]; //main array of all vertices
	Edg e[noe];

public:
	View(int a, int b);
}


