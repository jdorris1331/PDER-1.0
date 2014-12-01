/*********************************************************
*     *****
*    *~~~~~*   Partial Differential Equations Resource
*     *o o*              (PDER)
*     *  *
*     * *     By: Joseph Dorris, Joey Allen, ALex Kotzman
*    **                   and Wilson Parker
*   *
*********************************************************/

#ifndef OPERATORS_DEF
#define OPERATORS_DEF

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include "variable.h"

using namespace std;

//supported operators
VAR* ustp(VAR*);
VAR* rand(VAR*);
VAR* add(VAR* A, VAR* B);
VAR* sub(VAR* A, VAR* B);
VAR* mult(VAR* A, VAR* B);
VAR* divide(VAR* A, VAR* B);
VAR* grad(VAR* A);
VAR* curl(VAR* A);
VAR* diverg(VAR* A);
VAR* laplac(VAR* A);
VAR* vmod(VAR* A,VAR* B);
VAR* mag(VAR* A);

double sdiff(VAR* A, int x, int y, int z, int d);
double cdf(VAR* A, int x, int y, int z, int v, int d);

#endif
