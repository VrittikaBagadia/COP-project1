
#ifndef MAIN5CPP_H
#define MAIN5CPP_H
#include <QDebug>
//extern QString s;
//extern char *files;
//QString retstr();
#include<fstream>
#include<iostream>
#include<vector>


class Vert
{
public:

   double c1, c2;
   Vert()
   {
      c1=0;
      c2=0;
   }
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
   Vert3()
   {
      x=0;
      y=0;
      z=0;
   }
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
   Edg()
   {
       Vert v(0,0);
       s=v;
       e=v;
   }
   Edg (Vert i1, Vert i2)
   {
      s=i1;
      e=i2;
   }
};


class main5cpp
{
public:
    main5cpp();
};
std::vector <Edg3> trial();


#endif // MAIN5CPP_H
