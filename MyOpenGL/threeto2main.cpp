#include "threeto2main.h"

ThreeTo2Main::ThreeTo2Main()
{}
#include <math.h>
#include <QtCore>
#include <QtGui>
#include <fstream>
#include<iostream>
#include<vector>
#include<map>
#include<armadillo>
#include <qlabel.h>


//#include "transform.h"
#include "orthographic.h"
#include "orthographic_yz.h"
#include "orthographic_xz.h"
#include "isometric.h"
#include "classes.h"


using namespace Qt;
using namespace std;
using namespace arma;

int height = 800;
int width = 800;
double x,y,z, xiso, yiso;
double fx, fy,f, fiso, fisoy;


mat transformation_matrix(double x, double y, double z)
{
    /* code */
    // double x,y,z;
    // cin>>x>>y>>z;
    mat result;

    if (x==0 && y==0)
        result<<1<<0<<0<<endr<<0<<1<<0<<endr<<0<<0<<1<<endr;
    else if (y==0 && z==0)
        result<<1<<0<<0<<endr<<0<<1<<0<<endr<<0<<0<<1<<endr;
    else if (x==0 && z==0)
        result<<1<<0<<0<<endr<<0<<1<<0<<endr<<0<<0<<1<<endr;
    else
    {
        double den = sqrt(x*x + y*y + z*z);
        double cx = x/den;
        double cy = y/den;
        double cz = z/den;

        double d = sqrt(cy*cy + cz*cz);

        double cosalpha = cz/d;
        double sinalpha = cy/d;

        double cosbeta = d;
        double sinbeta = cx;

        //cout<<"\ncosalpha"<<cosalpha<<"\nsinalpha"<<sinalpha<<"\ncosbeta"<<cosbeta<<"\nsinbeta"<<sinbeta;

        mat rxalpha, rybeta;

        rxalpha<<1<<0<<0<<endr<<0<<cosalpha<<(-1*sinalpha)<<endr<<0<<sinalpha<<cosalpha<<endr;
        rybeta<<cosbeta<<0<<(-1*sinbeta)<<endr<<0<<1<<0<<endr<<sinbeta<<0<<cosbeta<<endr;

        // mat m;
        // m<<1<<0<<0<<endr<<0<<1<<0<<endr<<0<<0<<0<<endr;
        // trans(rxalpha)
        // trans(rybeta)
        //trans(rxalpha)*trans(rybeta)*m*
        // cout<<'\n'<<rxalpha<<'\n'<<rybeta;
        result=rybeta * rxalpha ;		// CHECK ORDER

    }

    //cout<<endl<<result;
    return result;
}



void print(vector<edge_final> e, QPainter &p, int quad)
{
    double xi, yi;

    if(quad==1)
    {
        xi=400-z;
        yi=400-y;
        fy*=-1;
        fx*=-1;
    }
    if(quad==2)
    {
        xi=400+x;
        yi=400-y;
        fy*=-1;
    }
    if(quad==3)
    {
        xi=xiso;
        yi=800-yiso;
        fisoy*=-1;
    }
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
                if(quad!=3)
                p.drawLine(fx*x1+xi,fy*y1+yi,fx*x2+xi,fy*y2+yi);
                else
                p.drawLine(fiso*x1+xi,fisoy*y1+yi,fiso*x2+xi,fisoy*y2+yi);


            }
            else
            {
                p.setPen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap));
                if(quad!=3)
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
    if(quad==3) {
//		x-=200;
        fisoy*=-1;}
//	if(quad==4) {
//		x-=600;
//		y-=600;}

}

//int threeDto2D (bool dr , char* filename)
int threeDto2D(bool dr, char* filename)
//int main(int argc, char *argv[])
{
   //QApplication a(null, null);
   QLabel l;
   QPicture pi;
   QPainter p(&pi);

   p.setRenderHint(QPainter::Antialiasing);
   //p.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
   //QPen pen1(Qt::black, 3, Qt::SolidLine, Qt::RoundCap);
   //QPen pen2(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap);


    ifstream infile;
    infile.open(filename);
    //infile.open(filename);

    double cx,cy,cz;
    infile>>cx>>cy>>cz;
//if (dr)
    mat tm = transformation_matrix(cx,cy,cz);		// TRANSFORMATION MATRIX
//else
//	mat tm = transformation_matrix(0,0,1);

   vector<edge_final> e_xy, e_yz, e_xz, e_iso;
   e_xy = main2xy(tm, filename);
   e_yz = main2yz(tm, filename);
   e_xz = main2xz(tm, filename);
   e_iso = mainiso(tm, filename);


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


    double maxxi = -99999 , maxyi = -99999, difxi, difyi;
    double minxi = 99999, minyi=99999;
    for (int i=0; i<e_iso.size(); i++)
    {
        if (e_iso.at(i).p1.x > maxxi)
            maxxi = e_iso.at(i).p1.x;

        if (e_iso.at(i).p1.x < minxi)
            minxi = e_iso.at(i).p1.x;

        if (e_iso.at(i).p2.x > maxxi)
            maxxi = e_iso.at(i).p2.x;

        if (e_iso.at(i).p2.x < minxi)
            minxi = e_iso.at(i).p2.x;

        if (e_iso.at(i).p1.y > maxyi)
            maxyi = e_iso.at(i).p1.y;

        if (e_iso.at(i).p1.y < minyi)
            minyi = e_iso.at(i).p1.y;

        if (e_iso.at(i).p2.y > maxyi)
            maxyi = e_iso.at(i).p2.y;

        if (e_iso.at(i).p2.y < minyi)
            minyi = e_iso.at(i).p2.y;

    }

    difz=maxz-minz;
    dify=maxy-miny;
    difx=maxx-minx;

    //cout<<"min y : "<<miny;

    if(difx>=dify and difx>=difz) f=380/difx;
    else if(dify>=difx and dify>=difz) f=380/dify;
    else f=380/difz;
    fy=f;
    fx=f;
    x=10-f*minx;
    y=10-f*miny;
    z=10-f*minz;

    //cout<<"min y :::: "<<y;


    difyi=maxyi-minyi;
    difxi=maxxi-minxi;

    //cout<<"min y : "<<miny;

    if(difxi>=difyi) fiso=380/difxi;
    else fiso=380/difyi;

    xiso=10-fiso*minxi;
    yiso=10-fiso*minyi;
    fisoy=fiso;


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
    print(e_iso, p, 3);

   p.end(); // Don't forget this line!
   l.setPicture(pi);
   l.show();
   return 0;
           //a.exec();
}
