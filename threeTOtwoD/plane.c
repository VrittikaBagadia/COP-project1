//Plane.h
class Plane
{
	private:
		bool cutting;
		double a,b,c,d;
	public:
		bool is_cutting();	///<returns true if cutting plane
		double[3][3] create_matrix();	///<how do we return a 2d matrix
};