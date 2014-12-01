/**
 * @file VariableList.cpp
 *
 * @brief The class VariableList can manages a list with variables.
 *
 * @license
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 *
 * Copyright (C) 2007-2011 Jos de Jong, http://www.speqmath.com
 *
 * @author 	Jos de Jong, <wjosdejong@gmail.com>
 * @date	2007, updated 2012-02-06
 */

/*********************************************************
*     *****
*    *~~~~~*   Partial Differential Equations Resource
*     *o o*              (PDER)
*     *  *
*     * *     By: Joseph Dorris, Joey Allen, ALex Kotzman
*    **                   and Wilson Parker
*   *
*********************************************************/

#include "variablelist.h"
#include <iostream>

/*
 * Initialize the size of the space
 */
Variablelist::Variablelist() {
  var.reserve(100);
}

Variablelist::~Variablelist() {
}

/*
 * Returns true if the given name already exists in the variable list
 */
bool Variablelist::exist(const char* name)
{
    return (get_id(name) != -1);
}


/*
 * Add a name of a certain type to the variable list
 */
bool Variablelist::add(const char* name, const int type)
{
    //see if the variable is already in the list
    int id = get_id(name);
    if (id == -1)
    {
        //create new var
        var.resize(var.size()+1);
        //name it
        strncpy(var[var.size()-1].name,name,30);
        //set initial ranges
        id = get_id(name);
        set_range(name,0,-99999999,9999999);
        set_range(name,1,-99999999,9999999);
        // set it to desired type
        var[id].set_type(type);
    }
    else
    {
        // variable already exists. overwrite it
        var[id].set_type(type);
    }
    return true;
}

/*
 * Add a name and variable to the variablelist
 */
bool Variablelist::add(const char* name, VAR * temp)
{
    int id = get_id(name);
    if (id == -1)
    {
        var.resize(var.size()+1);
        strncpy(var[var.size()-1].name,name,30);
        id = get_id(name);
        var[id].set_type(temp->get_type());
        var[id] = *temp;
        set_range(name,0,-99999999,9999999);
        set_range(name,1,-99999999,9999999);
        delete temp;

    }
    else
    {
        // variable already exists. overwrite it
        var[id].set_type(temp->get_type());
        var[id] = *temp;
        delete temp;
    }
    return true;
}

/*
 * Delete given variablename from the variable list
 */
bool Variablelist::del(const char* name)
{
    int id = get_id(name);
    if (id != -1)
    {
        var[id] = var[var.size()-1]; // move last item to deleted item
        // free memory
        var.pop_back();              // remove last item
        return true;
    }
    return false;
}

/*
 * Print desired stuff for debugging
 */
void Variablelist::print()
{
  for(int i=0;i<var.size();i++) {
    cout << var[i].name << " " << var[i].get_type() << endl;
    if(var[i].get_type()==0) cout << var[i].val << "\n"; 
    if(var[i].get_type()==1) cout << var[i].sf[1][2][3] << "\n";
    if(var[i].get_type()==2) cout << var[i].vf[0][0][0][0] << endl;
    cout << "Show range min=" << var[i].show_min << endl;
    cout << "Show range max=" << var[i].show_max << endl;
    cout << "Warn range min=" << var[i].warn_min << endl;
    cout << "Warn range min=" << var[i].warn_max << endl;
  }
}

/*
 * Get the type of the specified variable
 */
int Variablelist::get_type(const char* name)
{
    int id = get_id(name);
    return var[id].get_type();
}

/*
 * Get variable with given name
 */
bool Variablelist::get_variable(const char* name, VAR* ret_var)
{
    int id = get_id(name);
    if (id != -1)
    {
        *ret_var = var[id];
        return true;
    }
    return false;
}


/*
 * Get variable with given id
 */
bool Variablelist::get_variable(const int id, VAR* ret_var)
{
    if (id >= 0 && id < (int)var.size())
    {
        *ret_var = var[id];
        return true;
    }
    return false;
}

/*
 * Set the single value of the variable 
 */
bool Variablelist::set_value(const char* name,  double value)
{
    int id = get_id(name);
    if(var[id].get_type()!=0 && var[id].get_type()!=-1) {
      return false;
    }
    var[id].val = value;
    return true;
}


/* 
 * Set a specific value in  scalar field for this type of variable
 */
bool Variablelist::set_scalar_single(const char* name, int i, int j, int k, const double val) {
  int id = get_id(name);
  if(var[id].get_type()==1) {
    var[id].sf[i][j][k] = val;
    return true;
  }
  return false;
}

/* 
 * Set the scalar field for this type of variable
 */
bool Variablelist::set_scalar_field(const char* name, const double value) {
  int id = get_id(name);
  var[id].set_type(1);
  if(var[id].get_type()==1) {
    for(int i=0;i<DIM_SIZE;i++) {
      for(int j=0;j<DIM_SIZE;j++) {
        for(int k=0;k<DIM_SIZE;k++) {
          var[id].sf[i][j][k] = value;
        }
      }
    }
    return true;
  }
  else return false;
}


/* 
 * Set a specific location of vector field for this type of variable
 */
bool Variablelist::set_vector_single(const char* name, int i, int j, int k, int dir, const double val) {
  int id = get_id(name);
  if(var[id].get_type()==2) {
    var[id].vf[i][j][k][dir] = val;
    return true;
  }
  return false;
}


/*
 * Set the vector field for this type of variable
 */
bool Variablelist::set_vector_field(const char* name, const double value) {
  int id = get_id(name);
  var[id].set_type(2);
  if(var[id].get_type()==2) {
    for(int i=0;i<DIM_SIZE;i++) {
      for(int j=0;j<DIM_SIZE;j++) {
        for(int k=0;k<DIM_SIZE;k++) {
          for(int l=0;l<3;l++) {
            var[id].vf[i][j][k][l] = value;
            //cout << var[id].vf[i][j][k][l] << endl;
          }
        }
      }
    }
    return true;
  }
  else return false;
}

/*
 * Set ranges for a variable
 */
bool Variablelist::set_range(const char* name, const int type, const double min, const double max) {
  int id = get_id(name);
  if(id==-1) return false;
  if(type==0) {
    var[id].show_min=min;
    var[id].show_max=max;
    return true;
  }
  else if(type==1){
    var[id].warn_min=min;
    var[id].warn_max=max;
    return true; 
  }
  return false;
}

/*
 *  Get a range value for a variable
 */ 
double Variablelist::get_range(const char* name, const int type, const int LorH) {
  int id  = get_id(name);
  if(id==-1) return -1;
  if(type==0) {
    if(LorH==0) return var[id].show_min;
    else return var[id].show_max;
  }
  else if(type==1){
    if(LorH==0) return var[id].warn_min;
    else return var[id].warn_max;
  }
  else return -1;
}


/*
 * Returns the id of the given name in the variable list. Returns -1 if name
 * is not present in the list. Name is case insensitive
 */
int Variablelist::get_id(const char* name)
{
    // first make the name uppercase
    char nameU[NAME_LEN_MAX+1];
    char varU[NAME_LEN_MAX+1];
    toupper(nameU, name);

    for (unsigned int i = 0; i < var.size(); i++)
    {
        toupper(varU, var[i].name);
        if (strcmp(nameU, varU) == 0)
        {
            return i;
        }
    }
    return -1;
}


/*
 * str is copied to upper and made uppercase
 * upper is the returned string
 * str should be null-terminated
 */
void toupper(char upper[], const char str[])
{
    int i = -1;
    do
    {
        i++;
        upper[i] = std::toupper(str[i]);
    }
    while (str[i] != '\0');
}
