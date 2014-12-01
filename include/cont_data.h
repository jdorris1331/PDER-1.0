#ifndef CONT_DATA_H
#define CONT_DATA_H

#include <mgl2/fltk.h>
#include "variable.h"
#include "normalizer.h"
#include "constants.h"
#include "expression_parser.h"
#include "infile_parser.h"
#include "variablelist.h"
#include <string>
#include <vector>

using namespace std;

struct cont_data {
	cont_data();
	~cont_data();
	int parse(string file);
	int solve();
	Variablelist * vList;
	vector<string> *equations;
	int *hide;
	int *priority;
	double *colors;
	mglData x,y,z,c;
	mglData ex,ey,ez; 
	int vect_num;
}; 

#endif
