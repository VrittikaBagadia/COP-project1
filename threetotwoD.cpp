#include<fstream>
#include<iostream>
#include<vector>
#include<armadillo>
#include<map>
#include "transform.h"

using namespace std;
using namespace arma;
class vertex
{
	public:
		double x;
		double y;
		double z;
		vertex (double i1, double i2, double i3)
		{
			x=i1;
			y=i2;
			z=i3;
		}
};
class pair2
{
	public:
		double x;
		double y; 
		pair2 (double i1, double i2)
		{
			x=i1;
			y=i2;
		}
		bool operator<(const pair2& src)const
	    {
	        return (this->x < src.x)&& (this->y < src.y);
	    }

		bool operator == (const pair2& rhs) const
		{
			return (x==rhs.x)&&(y==rhs.y);
		}
};
class edge
{
	public:
		int x;
		int y;
		bool hidden;
		edge(int e1, int e2, bool b)
		{
			x = e1;
			y = e2;
			hidden = b;
		}
		bool operator == (const edge& rhs) const
		{
			return (x==rhs.x)&&(y==rhs.y);
		}
};

int main()
{
	ifstream infile; 
   	infile.open("input3to2.txt");

	double cx,cy,cz;
	infile>>cx>>cy>>cz;
	mat tm = transformation_matrix(cx,cy,cz);		// TRANSFORMATION MATRIX

	cout<<"direction ratios: "<<cx<<'\t'<<cy<<'\t'<<cz<<'\n';

	vector<vertex> vertices;						// INPUT VERTICES (AS A VECTOR) - vertices
	int vertices_no;								// no of input vertices
	double x,y,z;
	
   	infile>>vertices_no;
   	for (int i=0;i<vertices_no;i++)
   	{
   		infile>>x>>y>>z;
   		vertex v(x,y,z);
   		vertices.push_back(v);
   		
   	}
   	cout<<"no of vertices: "<<vertices.size()<<'\n';
   	vector <vertex> :: iterator i;
   	vector<pair2>:: iterator j;

   	vector<vertex> points;											// points - OUTPUT POINTS with z coord
   	//int points_no;

   	for (i = vertices.begin(); i != vertices.end(); ++i)
   	{
   		mat m;
   		m<<(*i).x<<endr<<(*i).y<<endr<<(*i).z<<endr;

 		mat projected_point = tm * m;			// CHECK ORDER

 		// cout<<projected_point(0)<<'\t';
 		// cout<<projected_point(1)<<'\t';
 		// cout<<projected_point(2)<<'\n';

 		vertex v(projected_point(0), projected_point(1), projected_point(2));
 		points.push_back(v);

   	}

   	// sort in increasing order of z coordinates
   	vector<int> orderofpoints;
   	for (int i=0; i<vertices_no; i++)
   		orderofpoints.push_back(i);
   	for (int i=0; i< vertices_no-1; i++)
   		for (int j=0; j<vertices_no-1-i; j++)
   			if ((points.at(orderofpoints[j]).z)>(points.at(orderofpoints[j+1]).z))
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
   	vector <edge> :: iterator e;

   	vector<edge> edges;


   	for(int i=0; i<edges_no; i++)
   	{
   		int end1,end2;
   		infile>>end1>>end2;
   		edge temp(end1,end2,false);
   		edges.push_back(temp);		// remove this
   		// pair2 temp2(mapping[end1-1]+1,mapping[end2-1]+1);
   		// newedges.push_back(temp2);
   	}

   	vector<edge> ordered_edges;
   	for (int i=0; i<vertices_no; i++)
   	{
   		int one = orderofpoints[i]+1;
   		for (int j=0; j<edges_no; j++)
   			if ( (edges[j].x)==one || (edges[j].y)== one)
   			{
   				e = find(ordered_edges.begin(), ordered_edges.end(), edges[j]);
   				if (e== ordered_edges.end())
   					ordered_edges.push_back(edges[j]);
   			}
   	}

   	cout<<"\nORDERED EDGES :\n ";
   	for (int i=0; i<edges_no;i++)
   		cout<<(ordered_edges.at(i)).x<<'\t'<<(ordered_edges.at(i)).y<<'\n';


   	////////////////////////////////////////////////////////////////////////////////////////////////


   	map<int,int> mapping;
   	vector<pair2> uniquepoints;
   	for (int i=0; i<vertices_no; i++)
   	{
   		vector<pair2>::iterator iter;
   		pair2 temp( (points.at(i)).x , (points.at(i)).y);
		iter = find(uniquepoints.begin(), uniquepoints.end(), temp);
	    if(iter != uniquepoints.end())
	    {
	    	mapping[i] = (iter - uniquepoints.begin()); ///////////////// WHAT IS THIS?????
	    	//cout<<mapping[i];
	    }
	    else
	    {
	    	mapping[i] = uniquepoints.size();		///// check
	    	uniquepoints.push_back(temp);
	    	
	    }
   	}

   	/* for printing the projected points */

   	cout<<endl<<"points "<<endl;
   	for (i = points.begin(); i != points.end(); ++i)
   	{
        cout << (*i).x<<'\t'<< (*i).y<<'\t'<< (*i).z << '\n';
   	} 


	cout<<endl<<"unique points "<<endl;									
   	for (j = uniquepoints.begin(); j != uniquepoints.end(); ++j)
   	{
        cout << (*j).x<<'\t'<< (*j).y<<'\n';
   	} 


   	// cout<<endl<<"mapping hashmap "<<endl;
   	// cout<<"hashmap size "<<mapping.size()<<endl;
   	// for(int i=0; i<mapping.size(); i++)
   	// 	cout<<mapping[i]<<'\t';

   	//////////////////////////////////////////////////////////////////////////////////////////


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

   	cout<<"\n FACE RECORD: \n";

   	for (int i=0; i<face_no; i++)
   	{
   		cout<<"face "<<i<<" :  ";
   		for (int j=0; j<face_record[i].size(); j++)
   		{
   			cout<<face_record[i].at(j)<<'\t';
   			
   		}
   		cout<<endl;
   	}

   	cout<<"\n EDGE RECORD \n";
   	for (int i=0; i<edges_no; i++)
   	{
   		cout<<"edge "<<i<< " :  ";
   		for (int j=0; j<edge_record[i].size(); j++)
   			cout<<edge_record[i].at(j)<<'\t';
   		cout<<endl;
   	}

   	//modifying ordered edges
   	for (int i=0; i<edges_no; i++)
   	{
   		int n1 = mapping[(ordered_edges.at(i).x)-1]+1;
   		int n2 = mapping[(ordered_edges.at(i).y)-1]+1;
   		edge temp(n1,n2,false);
   		ordered_edges.at(i) = temp;
   	}


   	cout<<"\n NEW ORDERED EDGES :\n ";
   	for (int i=0; i<edges_no;i++)
   		cout<<(ordered_edges.at(i)).x<<'\t'<<(ordered_edges.at(i)).y<<'\n';


   	//////////////////////////////////////////////////////////////////////////////////////////


	vector<edge> plotted;


   	for (int i=0; i<edges_no; i++)
   	{
   		//plotted.push_back(ordered_edges.at(i));					// recording plotted edges

   		//edges till ordered_edges[i] have been plotted

   		for (int j=0; j<edge_record[i].size(); j++)				// marking plotted edges for faces
   		{
   			int fn = edge_record[i].at(j);	// for edge 0 - fn will take values 0 and 5
   			face_record[fn].at(1) += 1;

   			if (face_record[fn].at(0) == face_record[fn].at(1))		// check face completion
   			{
   				vector<int> points_face;
   				for(int k=2; k<face_record[fn].size(); k++)
   				{
   					vector<int>::iterator ite;
   					int en = face_record[fn].at(k); //edge no.
   					int t1 = ordered_edges[en].x;
   					int t2 = ordered_edges[en].y;
   					ite = find (points_face.begin(), points_face.end(),t1);
   					if(ite==points_face.end())
   						points_face.push_back(t1);

   					ite = find (points_face.begin(), points_face.end(),t2);
   					if(ite==points_face.end())
   						points_face.push_back(t2);
   				}

   				// plotted - vector<edge> of plotted edges

   				for (int k=0; k<=i; k++)	// traversing the plotted points
   				{
   					if (ordered_edges[k].hidden == false)
					{
						int q;
						for (q=2; q<face_record[fn].size(); q++)
   						if (face_record[fn].at(q)==k)
   							break;
	   					if (q==face_record[fn].size())
	   					{
	   						// k th edge not found
	   						//check if it is to be hidden
	   						int t1 = ordered_edges[k].x;
	   						int t2 = ordered_edges[k].y;
	   						vector<int>::iterator ite;
	   						ite = find (points_face.begin(), points_face.end(), t1);
	   						if (ite!=points_face.end())
	   						{
	   							ite = find (points_face.begin(), points_face.end(), t2);
	   							if (ite!=points_face.end())
	   								ordered_edges[k].hidden = true;
	   								// both end points in the set hence the edge is to be hidden									
	   						}
	   					}
					}			
   				}
   			}
   		}
   	}

	cout<<endl<<"FINAL POINTS "<<endl;								
   	for (j = uniquepoints.begin(); j != uniquepoints.end(); ++j)
        cout << (*j).x<<'\t'<< (*j).y<<'\n';
   	cout<<"\n FINAL EDGES :\n ";
   	for (int i=0; i<edges_no;i++)
   		cout<<(ordered_edges.at(i)).x<<'\t'<<(ordered_edges.at(i)).y<<'\t'<<(ordered_edges.at(i)).hidden<<'\n';




   	///////////////////////////////////////////////////////////////////////////////////////////////////


   	






   	
   	

   	// vector<pair2> edges;							// edges can be removed (only for testing)
    // vector<pair2> newedges;

   	// for(int i=0; i<edges_no; i++)
   	// {
   	// 	int end1,end2;
   	// 	infile>>end1>>end2;
   	// 	pair2 temp(end1,end2);		//remove this
   	// 	edges.push_back(temp);		// remove this
   	// 	pair2 temp2(mapping[end1-1]+1,mapping[end2-1]+1);
   	// 	newedges.push_back(temp2);

   	// }

   	// cout<<"\nINPUT EDGES: \n";
   	// for (j=edges.begin(); j!=edges.end(); ++j)
   	// 	cout << (*j).x<<'\t'<< (*j).y<<'\n';

   	// cout<<"\nOUTPUT EDGES: \n";
   	// for (j=newedges.begin(); j!=newedges.end(); ++j)
   	// 	cout << (*j).x<<'\t'<< (*j).y<<'\n';

   	// vector<pair2> uniquenewedges;
   	// for (int i=0; i<edges_no; i++)
   	// {
   	// 	vector<pair2>::iterator iter;
   	// 	iter = find(uniquenewedges.begin(), uniquenewedges.end(), newedges.at(i));
   	// 	if (iter== uniquenewedges.end())
   	// 		if( (newedges.at(i)).x != (newedges.at(i)).y )
   	// 			uniquenewedges.push_back(newedges.at(i));
   	// }

   	// cout<<"\nUNIQUE OUTPUT EDGES: \n";
   	// for (j=uniquenewedges.begin(); j!=uniquenewedges.end(); ++j)
   	// 	cout << (*j).x<<'\t'<< (*j).y<<'\n';



   	return 0;
}




 //   	map<int,int>::iterator it;
	// for (mapping.begin(); it != mapping.end(); it++)
	// {
	// 	cout << it->first << " :: " << it->second << endl;
	// }
// std::map<int,int> mapping;
// for (int i=0; i<vertices_no; i++)
// {

// 	vector<vertex>::iterator iter;
// 	iter = find(point.begin(), points.end(), points.at(i));
// 	if(iter!=points.end())
// 	{
// 		//found
// 		mapping[i]=(iter - vert.begin());
// 	}
// 	else
// 	    {
// 	        m[i]=(vert.size());
// 	        vert.push_back(temp);
// 			//m.insert(pair <int, int> (i,vert.size()) );
// 	    }

// }
   	



   	

//    	std::map<pair2,int> twoD;							// twoD - hash map containing unique points
//    	std::map<pair2,int>::iterator it;

//    	std::map<int,int> mapping;
//    	cout<<endl<<vertices_no<<endl;

   	


//    	for (int i=0; i<vertices_no; i++)
//    	{
//    		pair2 p((points.at(i)).x, (points.at(i)).y);
//    		cout<<p.x<<"  "<<p.y<<endl;

//    		it = twoD.find(p);
//    		if (it == twoD.end())
//    		{
//    			//cout<<endl<<(*it).first.x;
//    			twoD.insert(pair<pair2,int>(p,i));
//    			mapping[i]=i;
//    		}
//    		else
//    		{
//    			//cout<<"else "<<i<<endl;
//    			mapping[i]=it->second;
//    		}
//    	}

//    	// std::map<int,int> twoD;
//    	// std::map<int,int>::iterator it;
//    	// for (int i=0; i<vertices_no; i++)
//    	// {

//    	// }


   	



//     map<pair2,int>::iterator iter=twoD.begin();
//     for(;iter!=twoD.end();++iter)
//     {
//         cout<<iter->second<<endl;
//     }