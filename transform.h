#include<iostream>
#include<armadillo>

using namespace std;
using namespace arma;

mat transformation_matrix(double x, double y, double z)
{
	/* code */
	// double x,y,z;
	// cin>>x>>y>>z;
	mat result;

	if (x==0 && y==0)
		result<<1<<0<<0<<endr<<0<<1<<0<<endr<<0<<0<<0<<endr;
	else if (y==0 && z==0)
		result<<0<<0<<0<<endr<<0<<1<<0<<endr<<0<<0<<1<<endr;
	else if (x==0 && z==0)
		result<<1<<0<<0<<endr<<0<<0<<0<<endr<<0<<0<<1<<endr;
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