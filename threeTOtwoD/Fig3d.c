//Fig3d.h
#include "Vertex.h"
#include "Edge.h"
#include "Face.h"
#include "Point.h"
class Fig3d
{
	private:
		int faceno, edgeno, vertexno; ///< might not be needed
		Face faces[12];
		Edge edges[50];
		Vertex vertices[50];

		int new_edges_no;
		Edge new_edges[50]; ///< gets value in case of cutting plane

		//something to store the hashed faces

	public:
		/**
		Sorts the input solid's vertices in decreasing order of distance from viewer
		(The point that is nearest to the plane of projection is first)
		*/
		void sort_vertices(Plane p);

		/**
		Calls vertex_to_point() for each vertex of the input 3D solid to generate the set of points of the 2D projection
		*/
		Point[] generate_2Dpoints( double matrix[3][3] );

		/**
		Will return a list of sides.
		The information about the side being hidden or not is updated through the data member hidden of the class Point
		*/
		Side[] generate_sides();

		/**
		Will make necessary changes in the solid and new_edges in case the plane specified is a cutting plane
		*/
		void create_new_solid(Plane p);

		/**
		To hash simple cycles formed by new_edges
		*/
		void hash();

		/**
		To unhash intersection of hashed portion and holes
		*/
		void unhash();
};