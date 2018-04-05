#include <math.h>
#include <QtCore>
#include <QtGui>
#include <fstream>
#include<iostream>
#include<vector>
#include<map>
#include<armadillo>
#include "try2.cpp"
#include "orthographic.cpp"
#include "orthographic_yz.cpp"
#include "orthographic_xz.cpp"
#define FACTOR 100
//#include "classes.h"
#include "transform.h"

using namespace Qt;
using namespace std;
using namespace arma;

int height = 800; 
int width = 800;
int x,y,z;
float fx, fy,f;

void print(vector<edge_final> e, QPainter &p, int quad)
{
	int xi, yi;

	if(quad==1) {
		xi=400-z;
		yi=400-y;
		fy*=-1;
		fx*=-1;}
	if(quad==2) {
		xi=400+x;
		yi=400-y;
		fy*=-1;}
//	if(quad==3) {
//		xi=400-y;
//		yi=z;}
	if(quad==4) {
		xi=400+x;
		yi=400+z;}
	
	for (int i=0; i<e.size(); i++)
   		{
   			

   			double x1 = e.at(i).p1.x;
   			double y1 = e.at(i).p1.y;
   			double x2 = e.at(i).p2.x;
   			double y2 = e.at(i).p2.y;

   			bool hid = e.at(i).hidden;
   			//cout<<x1<<y1<<x2<<y2<<'\n';

   			if(hid==false)
   			{
   				//solid line
   				p.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
   				p.drawLine(fx*x1+xi,fy*y1+yi,fx*x2+xi,fy*y2+yi);

   			}
   			else
   			{
   				p.setPen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap));
   				p.drawLine(fx*x1+xi,fy*y1+yi,fx*x2+xi,fy*y2+yi);
   			}
   		}

if(quad==1) {
//		x-=200;
//		y-=200;
	fy*=-1;
	fx*=-1;
}
	if(quad==2) {
		fy*=-1;}
//	if(quad==3) {
//		x-=200;
//		y-=600;}
//	if(quad==4) {
//		x-=600;
//		y-=600;}

}

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   QLabel l;
   QPicture pi;
   QPainter p(&pi);

   p.setRenderHint(QPainter::Antialiasing);
   //p.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
   //QPen pen1(Qt::black, 3, Qt::SolidLine, Qt::RoundCap);
   //QPen pen2(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap);


	ifstream infile; 
   	infile.open("input3.txt");
//if 
	double cx,cy,cz;
	infile>>cx>>cy>>cz;
	mat tm = transformation_matrix(cx,cy,cz);		// TRANSFORMATION MATRIX
// else tm<<I
   vector<edge_final> e_xy, e_yz, e_xz;
   e_xy = main2xy(tm);
   e_yz = main2yz(tm);
   e_xz = main2xz(tm);	


	double maxx = -99999 , maxy = -99999, maxz =-99999, difx, dify, difz;
	double minx = 99999, miny=99999, minz=99999;
	for (int i=0; i<e_xy.size(); i++)
	{
		if (e_xy.at(i).p1.x > maxx)
			maxx = e_xy.at(i).p1.x;

		if (e_xy.at(i).p1.x < minx)
			minx = e_xy.at(i).p1.x;

		if (e_xy.at(i).p2.x > maxx)
			maxx = e_xy.at(i).p2.x;

		if (e_xy.at(i).p2.x < minx)
			minx = e_xy.at(i).p2.x;

		if (e_xy.at(i).p1.y > maxy)
			maxy = e_xy.at(i).p1.y;

		if (e_xy.at(i).p1.y < miny)
			miny = e_xy.at(i).p1.y;

		if (e_xy.at(i).p2.y > maxy)
			maxy = e_xy.at(i).p2.y;

		if (e_xy.at(i).p2.y < miny)
			miny = e_xy.at(i).p2.y;
		
	}

	for (int i=0; i<e_yz.size(); i++)
	{
		
		if (e_yz.at(i).p1.x > maxz)
			maxz = e_yz.at(i).p1.x;

		if (e_yz.at(i).p1.x < minz)
			minz = e_yz.at(i).p1.x;

		if (e_yz.at(i).p2.x > maxz)
			maxz = e_yz.at(i).p2.x;

		if (e_yz.at(i).p2.x < minz)
			minz = e_yz.at(i).p2.x;
		
	}

	difz=maxz-minz;
	dify=maxy-miny;
	difx=maxx-minx;

	if(difx>=dify and difx>=difz) f=380/difx;
	else if(dify>=difx and dify>=difz) f=380/dify;
	else f=380/difz;
	fy=f;
	fx=f;
	x=10-f*minx;
	y=10-f*miny;
	z=10-f*minz;

	p.eraseRect(0,0,800,800);
	p.setPen(QPen(Qt::black,2));
	p.drawLine(0,0,width,0);
	p.drawLine(width,0,width,height);
	p.drawLine(width,height,0,height);
	p.drawLine(0,height,0,0);
	p.drawLine(width/2,0,width/2,height);
	p.drawLine(0,height/2,width,height/2);
   	
	print(e_xy, p, 2);
	print(e_yz, p, 1);
	print(e_xz, p, 4);
	
   p.end(); // Don't forget this line!
   l.setPicture(pi);
   l.show();
   return a.exec();
}
