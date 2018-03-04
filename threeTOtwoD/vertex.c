//Vertex.h
#include "Point.h"
#include "Plane.h"
class Vertex
{
	private:
		double x,y,z;
	public:
		Point vertex_to_point(double matrix[][]);	///<returns a point (converted to a 2d point by matrix multiplication)
		double distance_from_plane(Plane p);	///<returns the distance between the vertex and projection plane
};