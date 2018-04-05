#include<fstream>
#include<iostream>
#include<vector>
#include<armadillo>
#include<map>
//#include "transform.h"
#include "classes.h"
using namespace std;
using namespace arma;

// class vertex;
// class pair2;
// class edge;
// class edge_final;
vertex::vertex (double i1, double i2, double i3)
		{
			x=i1;
			y=i2;
			z=i3;
		}

pair2::pair2()
      		{
         		x=0;
         		y=0;
      		}
pair2::pair2 (double i1, double i2)
		{
			x=i1;
			y=i2;
		}
bool pair2::operator<(const pair2& src)const
	    	{
	        	return (this->x < src.x)&& (this->y < src.y);
	    	}

bool pair2::operator == (const pair2& rhs) const
		{
			return (x==rhs.x)&&(y==rhs.y);
		}
bool pair2::intersect (pair2 p1, pair2 p2)
		{
			if(y<max(p1.y,p2.y) && y>min(p1.y,p2.y))
			{
			double minv = (p2.x-p1.x)/(p2.y-p1.y);
			double maxx = ((y - p2.y)*minv) + p2.x;
			if (x <= maxx)			// check equality pe
				return true;
			}
   			return false; 
		}

edge::edge(int e1, int e2, bool b)
		{
			x = e1;
			y = e2;
			hidden = b;
		}
bool edge::operator == (const edge& rhs) const
		{
			return (x==rhs.x)&&(y==rhs.y);
		}

edge_final::edge_final ( pair2 source, pair2 destination, bool h)
		{
			p1.x = source.x;
			p1.y = source.y;

			p2.x = destination.x;
			p2.y = destination.y;

			hidden = h; 
		}





// class vertex
// {
// 	public:
// 		double x;
// 		double y;
// 		double z;
// 		vertex (double i1, double i2, double i3)
// 		{
// 			x=i1;
// 			y=i2;
// 			z=i3;
// 		}
// };
// class pair2
// {
// 	public:
// 		double x;
// 		double y; 
//       		pair2()
//       		{
//          		x=0;
//          		y=0;
//       		}
// 		pair2 (double i1, double i2)
// 		{
// 			x=i1;
// 			y=i2;
// 		}
// 		bool operator<(const pair2& src)const
// 	    	{
// 	        	return (this->x < src.x)&& (this->y < src.y);
// 	    	}

// 		bool operator == (const pair2& rhs) const
// 		{
// 			return (x==rhs.x)&&(y==rhs.y);
// 		}
// 		bool intersect (pair2 p1, pair2 p2)
// 		{
// 			if(y<max(p1.y,p2.y) && y>min(p1.y,p2.y))
// 			{
// 			double minv = (p2.x-p1.x)/(p2.y-p1.y);
// 			double maxx = ((y - p2.y)*minv) + p2.x;
// 			if (x <= maxx)			// check equality pe
// 				return true;
// 			}
//    			return false; 
// 		}
// };
// class edge
// {
// 	public:
// 		int x;
// 		int y;
// 		bool hidden;
// 		edge(int e1, int e2, bool b)
// 		{
// 			x = e1;
// 			y = e2;
// 			hidden = b;
// 		}
// 		bool operator == (const edge& rhs) const
// 		{
// 			return (x==rhs.x)&&(y==rhs.y);
// 		}
// };
// class edge_final
// {
// 	public:
// 		pair2 p1;
// 		pair2 p2;
// 		bool hidden;
// 		edge_final ( pair2 source, pair2 destination, bool h)
// 		{
// 			p1.x = source.x;
// 			p1.y = source.y;

// 			p2.x = destination.x;
// 			p2.y = destination.y;

// 			hidden = h; 
// 		}
// };



