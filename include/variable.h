/*********************************************************
*     *****
*    *~~~~~*   Partial Differential Equations Resource
*     *o o*              (PDER)
*     *  *
*     * *     By: Joseph Dorris, Joey Allen, ALex Kotzman
*    **                   and Wilson Parker
*   *
*********************************************************/

#ifndef VARIABLE_DEF
#define VARIABLE_DEF

#include "constants.h"

class VAR
{
  public:
    VAR();
    ~VAR();

    // copies over type and data
    VAR & operator=(const VAR &rhs);

    // name of VAR
    char name[NAME_LEN_MAX+1];

    // get and set for type
    void set_type(const int type);
    int get_type() const;

    // data
    double val;
    double *** sf;
    double **** vf;

    // ranges for sliders and warnings
    double warn_min;
    double warn_max;
    double show_min;
    double show_max;
  private:
    // type is set to private for memory management
    int type;
};

#endif
