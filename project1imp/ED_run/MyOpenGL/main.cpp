// main.cpp

#include <QApplication>
#include<iostream>
#include <QDesktopWidget>
#include<vector>
#include <QFileDialog>
//#include <QDebug>

#include<main_choice.h>
#include<fstream>
#include <math.h>
//#include <QtCore>
#include <QtGui>
#include<map>
#include<armadillo>
#include <qlabel.h>

//#include "transform.h"
#include "orthographic.h"
#include "orthographic_yz.h"
#include "orthographic_xz.h"
#include "isometric.h"
#include "classes.h"
#include "threeto2main.h"
#include "window.h"
#include "main5cpp.h"
//#include "ui_window.h"
//#include "ui_main_choice.h"


//extern char *files;
QString s="";
using namespace std;

#include "main_choice.h"
#include "ui_main_choice.h"
int op=1;
main_choice::main_choice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::main_choice)
{
    ui->setupUi(this);
}

main_choice::~main_choice()
{
    delete ui;
}
QString fn;
bool dr=true;
char *filename="input2.txt";
void main_choice::on_TwoD_to_3D_clicked()
{
    fn= QFileDialog::getOpenFileName(this, "Select file", QDir::currentPath());
    op=1;
    close();
}

void main_choice::on_ThreeD_to_2D_o_clicked()
{
   // QString
            fn= QFileDialog::getOpenFileName(this, "Select file", QDir::currentPath());
    dr=false;
    //filename=f.mid(f.lastIndexOf("/")+1).toLatin1().data();
    op=2;
    close();
}

void main_choice::on_ThreeD_to_2D_dr_clicked()
{
 //   QString
            fn= QFileDialog::getOpenFileName(this, "Select file", QDir::currentPath());
    dr=true;
    //filename=f.mid(f.lastIndexOf("/")+1).toLatin1().data();
    op=2;
    //int a= threeDto2D(true, f.mid(f.lastIndexOf("/")+1).toLatin1().data());
    close();
}

std::vector <Edg3> trial()
{

       ifstream infile;
       infile.open(fn.mid(fn.lastIndexOf("/")+1).toLatin1().data());

       int notv, noe; //number of total vertices
       infile>>notv>>noe;

       Vert view1[100];                // INPUT VERTICES (AS A VECTOR) - vertices
       Edg v1edg[100];

       double i1,i2, i3, i4;

          for (int i=0;i<notv;i++)
          {
             infile>>i1>>i2;
             Vert v(i1,i2);
             view1[i]=v;
          }

          for (int i=0;i<noe;i++)
          {
             infile>>i1>>i2>>i3>>i4;
             Vert v1(i1,i2);
             Vert v2(i3,i4);
             Edg e(v1, v2);
             v1edg[i]=e;
          }


          int noe2; //number of total vertices
          infile>>noe2;

       Vert view2[100];                // INPUT VERTICES (AS A VECTOR) - vertices
       Edg v2edg[100];

       for (int i=0;i<notv;i++)
          {
             infile>>i1>>i2;
             Vert v(i1,i2);
             view2[i]=v;
          }

          for (int i=0;i<noe2;i++)
          {
             infile>>i1>>i2>>i3>>i4;
             Vert v1(i1,i2);
             Vert v2(i3,i4);
             Edg e(v1, v2);
             v2edg[i]=e;
          }

          int noe3; //number of total vertices
          infile>>noe3;



       Vert view3[100];                // INPUT VERTICES (AS A VECTOR) - vertices
       Edg v3edg[100];

       for (int i=0;i<notv;i++)
          {
             infile>>i1>>i2;
             Vert v(i1,i2);
             view3[i]=v;
          }

          for (int i=0;i<noe3;i++)
          {
             infile>>i1>>i2>>i3>>i4;
             Vert v1(i1,i2);
             Vert v2(i3,i4);
             Edg e(v1, v2);
             v3edg[i]=e;
          }



          Vert3 sov[notv];
          std::vector<Edg3> eset;

          for (int i=0;i<notv;i++)
          {
             Vert3 v(view1[i], view2[i]);
             sov[i]=v;
          }
          bool add=false;
          for (int i = 0; i < noe; ++i)
          {
             for (int j = 0; j < notv; ++j)
             {

                    if(v1edg[i].s==view1[j])
                {

                   for (int k = 0; k < notv; ++k)
                   {

                      if(v1edg[i].e==view1[k])
                      {
                         add=true;
                         //check in view 2
                         //cout<<v1edg[i].e.c1<<v1edg[i].e.c2<<"  "<<view1[k].c1<<view1[k].c2;
                         if(!(view2[j]==view2[k]))
                         {
                            for (int m = 0; m < noe2; ++m)
                            {
                               if((v2edg[m].s==view2[j] and v2edg[m].e==view2[k]) or (v2edg[m].s==view2[k] and v2edg[m].e==view2[j]))
                               {
                                  add=true;
                                  break;
                               }
                               else add=false;
                            }
                         }

                         //cout<<v1edg[i].e.c1<<v1edg[i].e.c2;

                         //check in view3
                         if(!(view3[j]==view3[k]))
                         {
                            for (int m = 0; m < noe3; ++m)
                            {

                               if((v3edg[m].s==view3[j] and v3edg[m].e==view3[k]) or (v3edg[m].s==view3[k] and v3edg[m].e==view3[j]))
                               {
                                  add=add and true;
                                  break;
                               }
                               if(m==noe3-1) add=false;
                            }
                         }

                         if(add)
                         {
                            Edg3 e(sov[j], sov[k]);
                            eset.push_back(e);
                         }
                      }
                   }
                }
             }
          }


          std::vector <Edg3> :: iterator i;


          //edge between same points in view 1
          for (int i = 0; i < notv; ++i)
          {
             for (int j = i+1; j < notv; ++j)
             {
                if(view1[i]==view1[j])
                {
                add=true;
                //check in view 2
                for (int m = 0; m < noe2; ++m)
                {
                   if((v2edg[m].s==view2[i] and v2edg[m].e==view2[j]) or (v2edg[m].s==view2[j] and v2edg[m].e==view2[i]))
                   {
                      add=true;
                      break;
                   }
                   else add=false;
                }

                //check in view3
                for (int m = 0; m < noe3; ++m)
                {
                   if((v3edg[m].s==view3[j] and v3edg[m].e==view3[i]) or (v3edg[m].s==view3[i] and v3edg[m].e==view3[j]))
                   {

                      add=add and true;
                      break;
                   }
                   if(m==noe3-1) add=false;
                   //else add=false;
                }

                if(add)
                {
                   Edg3 e(sov[j], sov[i]);
                   eset.push_back(e);
                }
                }
             }
          }
        return eset;
//          vector <Edg3> :: iterator i;
//          // // for printing the input vertices
//          for (i = eset.begin(); i != eset.end(); ++i)
//          {
//              draw((*i).s.x, (*i).s.y,(*i).s.z,(*i).e.x,(*i).e.y,(*i).e.z));
//          }
    //}

}


ThreeTo2Main::ThreeTo2Main()
{}


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



int main(int argc, char *argv[])
{


    QApplication app(argc, argv);


    main_choice d;
    d.setModal(true);
    d.exec();
//QApplication::QApplication
//    QFileDialogTester test;
//    QString s;
//    s=test.openFile();
//    QFile file(s);
    //s.toLatin1().data();
  //  qDebug() << "kbxrh : " << (s.mid(s.lastIndexOf("/")+1).toLatin1().data());
                //file.fileName().toLatin1().data();
    //files= (s.mid(s.lastIndexOf("/")+1).toLatin1().data());
    //qDebug() << "kbxrh : " <<files;
    //////////////////////
    if(op==1){
    //QDesktopWidget::
    //QWidget::window()
               :: Window window;

    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();

    window.setWindowTitle("OpenGL with Qt");

    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();
    app.exec();
    }
    else {

                QLabel l;
                QPicture pi;
                QPainter p(&pi);

                p.setRenderHint(QPainter::Antialiasing);
                //p.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
                //QPen pen1(Qt::black, 3, Qt::SolidLine, Qt::RoundCap);
                //QPen pen2(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap);


                 ifstream infile;
                 //infile.open("input4.txt");
                 infile.open(fn.mid(fn.lastIndexOf("/")+1).toLatin1().data());

                 double cx,cy,cz;
                 infile>>cx>>cy>>cz;
                 mat tm;
             if (dr)
                 tm = transformation_matrix(cx,cy,cz);		// TRANSFORMATION MATRIX
             else
                 tm = transformation_matrix(0,0,1);

                vector<edge_final> e_xy, e_yz, e_xz, e_iso;
                e_xy = main2xy(tm, fn.mid(fn.lastIndexOf("/")+1).toLatin1().data());
                e_yz = main2yz(tm, fn.mid(fn.lastIndexOf("/")+1).toLatin1().data());
                e_xz = main2xz(tm, fn.mid(fn.lastIndexOf("/")+1).toLatin1().data());
                e_iso = mainiso(tm, fn.mid(fn.lastIndexOf("/")+1).toLatin1().data());


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
                //w.show();
                return
                        //0;
                        app.exec();
             }
}
