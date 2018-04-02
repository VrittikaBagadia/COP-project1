#include<fstream>
#include<iostream>
#include<vector>

using namespace std;

class Vert
{
public:
   Vert();
   double c1, c2;
   Vert (double i1, double i2)
      {
         c1=i1;
         c2=i2;
      }



   bool operator==(const Vert& rhs)
    {
        return (this->c1 == rhs.c1) && (this->c2== rhs.c2);
    }
};

class Vert3
{
public:
   double x, y, z;
   Vert3();
   Vert3 (Vert v1,Vert v2)
   {
      x=v1.c1;
      y=v1.c2;
      z=v2.c2;
   }
};

class Edg3
{
public:
   Vert3 s, e;
   Edg3();
   Edg3(Vert3 v1, Vert3 v2)
   {
      s=v1;
      e=v2;
   }
};

class Edg
{
public:
   Vert s, e;
   Edg();
   Edg (Vert i1, Vert i2)
   {
      s=i1;
      e=i2;
   }
};


int main()
{
   ifstream infile;
      infile.open("input.txt");

      int notv, noe; //number of total vertices
      infile>>notv>>noe;

   Vert view1[notv];                // INPUT VERTICES (AS A VECTOR) - vertices
   Edg v1edg[noe];

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

   Vert view2[notv];                // INPUT VERTICES (AS A VECTOR) - vertices
   Edg v2edg[noe2];

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

   Vert view3[notv];                // INPUT VERTICES (AS A VECTOR) - vertices
   Edg v3edg[noe3];

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
      vector<Edg3> eset;

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
               for (int k = 0; k < notv; ++j)
               {
                  if(v1edg[i].e==view1[k])
                  {
                     add=true;
                     //check in view 2
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
                           else add=false;
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
               else add=false;
            }

            if(add)
            {
               Edg3 e(sov[j], sov[i]);
               eset.push_back(e);
            }
            }
         }
      }



      vector <Edg3> :: iterator i;


      // for printing the input vertices


      for (i = eset.begin(); i != eset.end(); ++i)
      {
        cout << (*i).s.x<<" "<< (*i).s.y<<" "<< (*i).s.z << '\n';
        cout << (*i).e.x<<" "<< (*i).e.y<<" "<< (*i).e.z << '\n';
      }

return 0;
}


