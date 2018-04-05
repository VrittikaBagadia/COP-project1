#ifndef iso_
#define iso_

#include<fstream>
#include<iostream>
#include<vector>
#include<armadillo>
#include<map>

#include"classes.h"
using namespace std;
using namespace arma;



vector<edge_final> mainiso(mat tm, char* filename);

#endif
