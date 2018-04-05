#include "main5cpp.h"
#include<fstream>
#include<vector>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include "threeto2main.h"
using namespace std;

#include "main_choice.h"
#include "ui_main_choice.h"

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
void main_choice::on_TwoD_to_3D_clicked()
{
    fn= QFileDialog::getOpenFileName(this, "Select file", QDir::currentPath());
    close();
}

void main_choice::on_ThreeD_to_2D_o_clicked()
{
    QString f= QFileDialog::getOpenFileName(this, "Select file", QDir::currentPath());
    int a= threeDto2D(false, f.mid(f.lastIndexOf("/")+1).toLatin1().data());
    close();
}

void main_choice::on_ThreeD_to_2D_dr_clicked()
{
    QString f= QFileDialog::getOpenFileName(this, "Select file", QDir::currentPath());
    int a= threeDto2D(true, f.mid(f.lastIndexOf("/")+1).toLatin1().data());
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
