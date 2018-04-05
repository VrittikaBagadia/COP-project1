#include<fstream>
#include<iostream>
#include<vector>
#include<armadillo>
#include<map>

using namespace std;
using namespace arma;
#ifndef _CLASSES_
#define _CLASSES_


class vertex
{
	public:
		double x;
		double y;
		double z;
		vertex (double i1, double i2, double i3);
		//{x=i1;y=i2;z=i3;}
		
};
class pair2
{
	public:
		double x;
		double y; 
      		pair2();
		pair2 (double i1, double i2);
		bool operator<(const pair2& src)const ;
		bool operator == (const pair2& rhs) const ;
		bool intersect (pair2 p1, pair2 p2);
		
};
class edge
{
	public:
		int x;
		int y;
		bool hidden;
		edge(int e1, int e2, bool b);
		bool operator == (const edge& rhs) const;
};
class edge_final
{
	public:
		pair2 p1;
		pair2 p2;
		bool hidden;
		edge_final ( pair2 source, pair2 destination, bool h);
};

#endif

