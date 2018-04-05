#include<fstream>
#include<iostream>
#include<vector>
#include<armadillo>
#include<map>
//#include "classes.h"


using namespace std;
using namespace arma;

vector<edge_final> main2xz(mat tm)
//int main()
{
	ifstream infile; 
   	infile.open("input3.txt");


	double cx,cy,cz;////////////////////////
	infile>>cx>>cy>>cz;/////////////////////////


	vector<vertex> vertices, points;						// INPUT VERTICES (AS A VECTOR) - vertices
	int vertices_no;								// no of input vertices
	double x,y,z;
	
   	infile>>vertices_no;
   	for (int i=0;i<vertices_no;i++)
   	{
   		infile>>x>>z>>y;
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

 		vertex v(projected_point(0), projected_point(1), projected_point(2));
 		vertices.push_back(v);

   	}

   	
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

                        for (q=2; q<face_record[fn].size(); q++)        // traversing over all edges
                        {
                           int edge_no = face_record[fn].at(q);
                           edge e = ordered_edges[edge_no];
                           int e1 = e.x;  // e1 and e2 are indices in points
                           int e2 = e.y;
                           pair2 p1( vertices[e1-1].x, vertices[e1-1].y);
                           pair2 p2(vertices[e2-1].x , vertices[e2-1].y);

                           if(endpt1==p1 || endpt1==p2)
                              poly1 = true;
                           if(endpt2==p1 || endpt2==p2)
                              poly2 = true;

                           if (intersect(endpt1,p1,p2) == true)
                              intersection1+=1;
                           if (intersect(endpt2,p1,p2) == true)
                              intersection2+=1;

                        }
                        //cout<<"\nintersection1,intersection2: "<<intersection1<<'\t'<<intersection2<<'\n';
                        if (((intersection1%2==1) && (intersection2%2==1)) || (poly1 && (intersection2%2==1)) || ((intersection1%2==1)&& poly2) || (poly1 && poly2))       // both end points inside
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
