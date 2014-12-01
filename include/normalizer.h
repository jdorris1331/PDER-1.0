/*********************************************************
*     *****
*    *~~~~~*   Partial Differential Equations Resource
*     *o o*              (PDER)
*     *  *
*     * *     By: Joseph Dorris, Joey Allen, ALex Kotzman
*    **                   and Wilson Parker
*   *
*********************************************************/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <mgl2/fltk.h>

#include "variable.h"
#include "constants.h"

using namespace std;

void normalize_scalar(vector<VAR> *vars, int* hide, int* priority, double* color_values, mglData* x, mglData* y, mglData* z, mglData* plot_data);
void normalize_vector(vector<VAR> *vars, int vect_num, mglData* ex, mglData*ey, mglData* ez);
