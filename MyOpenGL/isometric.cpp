#include<math.h>
#include<fstream>
#include<iostream>
#include<vector>
#include<armadillo>
#include<map>

#include "classes.h"
#include "isometric.h"


using namespace std;
using namespace arma;


mat transformation_matrix1(double x, double y, double z)
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
      result=rybeta * rxalpha ;     // CHECK ORDER
      
   }

   //cout<<endl<<result;
   return result;
}


vector<edge_final> mainiso(mat tm , char* filename)
//int main()
{
	ifstream infile; 
   	infile.open(filename);


	double cx,cy,cz;////////////////////////
	infile>>cx>>cy>>cz;/////////////////////////


	vector<vertex> vertices_inter,vertices, points;						// INPUT VERTICES (AS A VECTOR) - vertices
	int vertices_no;								// no of input vertices
	double x,y,z;
	
   	infile>>vertices_no;
   	for (int i=0;i<vertices_no;i++)
   	{
   		//infile>>y>>z>>x;
         infile>>x>>y>>z;
		//z*=-1;
   		vertex v(x,y,z);
   		points.push_back(v);
   	}
   	//cout<<"no of vertices: "<<vertices.size()<<'\n';
   	vector <vertex> :: iterator i;
   	vector<pair2>:: iterator j;

	for (i = points.begin(); i != points.end(); ++i)
   	{
   		mat m;
   		m<<(*i).x<<endr<<(*i).y<<endr<<(*i).z<<endr;

 		mat projected_point = tm * m;			// CHECK ORDER

 		//vertex v(projected_point(0), projected_point(1), projected_point(2));
      //vertex v(projected_point(2), projected_point(0), projected_point(1));
      vertex v(projected_point(0), projected_point(1), projected_point(2));
 		vertices_inter.push_back(v);

   	}

   mat newmat = transformation_matrix1(1,1,1); 

   for (i = vertices_inter.begin(); i != vertices_inter.end(); ++i)
      {
         mat m;
         m<<(*i).x<<endr<<(*i).y<<endr<<(*i).z<<endr;

      mat projected_point = newmat * m;       // CHECK ORDER

      //vertex v(projected_point(0), projected_point(1), projected_point(2));
      //vertex v(projected_point(2), projected_point(0), projected_point(1));
      vertex v(projected_point(0), projected_point(1), projected_point(2));
      vertices.push_back(v);

      }

   //newmat<<1<<0<<0<<endr<<0<<cosalpha<<(-1*sinalpha)<<endr<<0<<sinalpha<<cosalpha<<endr;

   	
   	// sort in increasing order of z coordinates /////// according to the viewing direction
   	vector<int> orderofpoints;
   	for (int i=0; i<vertices_no; i++)
   		orderofpoints.push_back(i);
   	for (int i=0; i< vertices_no-1; i++)
   		for (int j=0; j<vertices_no-1-i; j++)
   			if ((vertices.at(orderofpoints[j]).z)>(vertices.at(orderofpoints[j+1]).z))
   			{
   				int temp = orderofpoints[j];
   				orderofpoints[j] = orderofpoints[j+1];
   				orderofpoints[j+1] = temp;
   			}
 
   	cout<<"ORDER OF POINTS\n ";
   	for (int i=0; i<vertices_no; i++)
   		cout<<orderofpoints[i]+1<<'\t';
   	cout<<endl;

   	//////////////////////////////////////////////////////////////////////////////////////////

   	int edges_no;
   	infile>>edges_no;
   	vector <int> :: iterator e1,e2;
      vector <edge> :: iterator e;

   	vector<edge> edges;


   	for(int i=0; i<edges_no; i++)
   	{
   		int end1,end2;
   		infile>>end1>>end2;
   		edge temp(end1,end2,false);
   		edges.push_back(temp);	
   	}

      vector<edge> ordered_edges;
      vector<int> plotted_points;
      for(int i=0; i<vertices_no; i++)
      {
         plotted_points.push_back(orderofpoints[i]+1);
         for (int j=0; j<edges_no; j++)
         {
            e1 = find(plotted_points.begin(), plotted_points.end(), edges[j].x);
            e2 = find(plotted_points.begin(), plotted_points.end(), edges[j].y);
            if (e1 != plotted_points.end() && e2 != plotted_points.end())
            {
               e=find(ordered_edges.begin(), ordered_edges.end(),edges[j]);
               if (e==ordered_edges.end())
                  ordered_edges.push_back(edges[j]);
            }
         }
      }

   	////////////////////////////////////////////////////////////////////////////////////////////////
      map<int,int> mapping;
      vector<pair2> uniquepoints;
      for (int i=0; i<vertices_no; i++)
      {
         vector<pair2>::iterator iter;
         pair2 temp( (vertices.at(i)).x , (vertices.at(i)).y);
      iter = find(uniquepoints.begin(), uniquepoints.end(), temp);
       if(iter != uniquepoints.end())
       {
         mapping[i] = (iter - uniquepoints.begin()); ///////////////// WHAT IS THIS?????
         //cout<<mapping[i];
       }
       else
       {
         mapping[i] = uniquepoints.size();      ///// check
         uniquepoints.push_back(temp);
         
       }
      }
   	////////////////////////////////////////////////////////////////////////////////////////////////


      //  RECORDING FACES AND EDGES
   	std::vector<int> face_record[30];	// assuming maximum number of faces to be 30
   	std::vector<int> edge_record [100];	// assuming max no of edges to be 100
   	int face_no;
   	infile>>face_no;
   	for (int i=0; i< face_no; i++)
   	{
   		int no_of_edges;
   		infile>>no_of_edges;

   		face_record[i].push_back(no_of_edges);
   		face_record[i].push_back(0);

   		for (int j=0; j<no_of_edges; j++)
   		{
   			int end1,end2;
   			infile>>end1;
   			infile>>end2;
   			int ne;
   			edge e1(end1,end2,false);
   			//e iterator declared above
   			e = find (ordered_edges.begin(), ordered_edges.end(), e1);
   			if (e==ordered_edges.end())
			{
				edge e2(end2,end1,false);
				e = find (ordered_edges.begin(), ordered_edges.end(), e2);
			}
   			ne = distance(ordered_edges.begin(),e);
   			face_record[i].push_back(ne);
   			edge_record[ne].push_back(i);

   		}
   	}

   	//////////////////////////////////////////////////////////////////////////////////////////


	vector<edge> plotted;
   	for (int i=0; i<edges_no; i++)
   	{
   		for (int j=0; j<edge_record[i].size(); j++)				// marking plotted edges for faces
   		{
   			int fn = edge_record[i].at(j);	
   			face_record[fn].at(1) += 1;   // incrementing the number of plotted edges

   			if (face_record[fn].at(0) == face_record[fn].at(1))		// check face completion
   			{
   				// plotted - vector<edge> of plotted edges
   				for (int k=0; k<=i; k++)	// traversing the plotted edges
   				{
   					if (ordered_edges[k].hidden == false) //////// ye shayad hataani padhe
   					{
   						int q;
   						for (q=2; q<face_record[fn].size(); q++)
      						if (face_record[fn].at(q)==k)
      							break;
	   					if (q==face_record[fn].size())
	   					{
	   						// k th edge not found i.e kth edge not a side of the face 'fn'
	   						//check if it is to be hidden


                        /////////////////.  EDIT HERE.   ////////////////////////////

                        // make hidden = true if both end points of ordered_edges[k] inside the face

                        int end1 = ordered_edges[k].x;
                        int end2 = ordered_edges[k].y;
                        pair2 endpt1 (vertices[end1-1].x , vertices[end1-1].y);
                        pair2 endpt2 (vertices[end2-1].x , vertices[end2-1].y);

                        int intersection1 = 0;
                        int intersection2 = 0;

                        bool poly1=false;
                        bool poly2=false;

                        std::vector<int> face_points;
                        vector<int>:: iterator ite;

                        for (q=2; q<face_record[fn].size(); q++)        // traversing over all edges
                        {
                           int edge_no = face_record[fn].at(q);
                           edge e = ordered_edges[edge_no];
                           int e1 = e.x;  // e1 and e2 are indices in points
                           int e2 = e.y;

                           ite = find (face_points.begin(), face_points.end(), e1 );
                           if (ite == face_points.end())
                              face_points.push_back(e1);

                           ite = find (face_points.begin(), face_points.end(), e2 );
                           if (ite == face_points.end())
                              face_points.push_back(e2);
                           pair2 p1( vertices[e1-1].x, vertices[e1-1].y);
                           pair2 p2(vertices[e2-1].x , vertices[e2-1].y);

                           if(endpt1==p1 || endpt1==p2)
                              poly1 = true;
                           if(endpt2==p1 || endpt2==p2)
                              poly2 = true;

                           if (endpt1.intersect(p1,p2) == true)
                              intersection1+=1;
                           if (endpt2.intersect(p1,p2) == true)
                              intersection2+=1;

                        }

                         if (intersection1%2==1)
                        {
                           //////////////////////////////////// face_points <int> , pair2 - endpt1
                           for (int i=0; i<face_points.size(); i++)
                           {
                              int n = face_points.at(i) - 1; // stores vertices numbers starting from 0

                              if ((vertices.at(n).y == endpt1.y)&&((vertices.at(n).x >= endpt1.x )))
                              {
                                 cout<<"\npt: "<<endpt1.x<<'\t'<<endpt1.y<<'\t'<<" ::: face: "<<fn<<endl;
                                 intersection1=0;
                              }
                           }
                        }

                        if (intersection2%2==1)
                        {
                           cout<<"\nenters this for face "<<fn<<" edge "<<k<<endl;
                           //////////////////////////////////// face_points <int> , pair2 - endpt1
                           for (int i=0; i<face_points.size(); i++)
                           {
                              int n = face_points.at(i) - 1; // stores vertices numbers starting from 0
                              if (k==7)
                                 cout<<n<<'\t'<<vertices.at(n).x<<'\t'<<vertices.at(n).y<<'\n';
                              if ((vertices.at(n).y == endpt2.y) && ((vertices.at(n).x >= endpt2.x )))
                              {
                                 cout<<"changed intersection for edge "<<k;
                                 intersection2=0;
                              }
                           }
                        }
                        //cout<<"\nintersection1,intersection2: "<<intersection1<<'\t'<<intersection2<<'\n';
                        //if (((intersection1%2==1) && (intersection2%2==1)) || (poly1 && (intersection2%2==1)) || ((intersection1%2==1)&& poly2) || (poly1 && poly2))       // both end points inside
			if (intersection1%2 == 1 || intersection2%2 == 1 || (poly1==1 && poly2==1))
                           ordered_edges[k].hidden = true;
	   					}
   					}			
   				}
   			}
   		}
   	}

      vector<edge_final> edgesf;

      //will return edgesf;
      for (int i=0; i<edges_no; i++)
      {
         int point1 = ordered_edges.at(i).x;
         int point2 = ordered_edges.at(i).y;
         bool hid = ordered_edges.at(i).hidden; 
         edge_final e (uniquepoints.at(mapping[point1-1]), uniquepoints.at(mapping[point2-1]), hid);
         edgesf.push_back(e);
      }
      infile.close();
      return edgesf;
      
      
   	///////////////////////////////////////////////////////////////////////////////////////////////////


   	//return 0;


}
