/*
#include "MglWrapper/MglWrapper.h"

void MglWrapper::loadData(int size, double* temp_x, double* temp_y, double* temp_z, double* temp_c)
{
    x = new mglData(size);
    y = new mglData(size);
    z = new mglData(size);
    c = new mglData(size);
    for(int i=0; i < size; i++)
    {
        x->a[i] = temp_x[i];
        y->a[i] = temp_y[i];
        z->a[i] = temp_z[i];
        c->a[i] = temp_c[i];
    }
}

void MglWrapper::plot()
{
    gr = new mglQT(setup,"3D_PDE");
}

int MglWrapper::setup(mglGraph *gr)
{
    gr->Title("Test 1");
    gr->Rotate(50,60);
    gr->Box();
    gr->Dots(x,y,z);
    return 0;
}
*/
