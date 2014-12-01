#include "cont_data.h"

cont_data::cont_data() {
  vList = new Variablelist();
  equations = new vector<string>;
  ex.Create(DIM_SIZE,DIM_SIZE,DIM_SIZE);  ey.Create(DIM_SIZE,DIM_SIZE,DIM_SIZE);  ez.Create(DIM_SIZE,DIM_SIZE,DIM_SIZE);
  vect_num=-1;
/*  x = new mglData;
  y = new mglData;
  z = new mglData;
  c = new mglData;
  ex = new mglData;
  ey = new mglData;
  ez = new mglData;*/
}

cont_data::~cont_data() {
  delete vList;
  delete equations;
  delete[] hide;
  delete[] priority;
  delete[] colors;
  /*delete x;
  delete y;
  delete z;
  delete c;
  delete ex;
  delete ey;
  delete ez;*/
}

int cont_data::parse(string file) {
  infile_parser fileP;
  fileP.parse(file.c_str(), vList, equations);
  hide = new int[vList->var.size()];
  priority = new int[vList->var.size()];
  colors = new double[vList->var.size()];
  for(int i=0;i<vList->var.size();i++) {
    priority[i]=i;
    if(!strcmp(vList->var[i].name,"X") || !strcmp(vList->var[i].name,"Y") || !strcmp(vList->var[i].name,"Z")) {
      hide[i]=1;
    }
    else hide[i]=0;
    colors[i]= (i+1.0)*10;
  }
  return 1;
}

int cont_data::solve() {
  Parser prs;
  char** eqs;
  eqs = new char*[equations->size()];
  for(int i=0;i<equations->size();i++) {
    eqs[i] = new char[255];
    memcpy(eqs[i],equations->at(i).c_str(),equations->at(i).size());
    eqs[i][equations->at(i).size()] = 0;
  //  cout << eqs[i] << endl;
  }

  prs.set_eqs(eqs, equations->size());
  prs.solve(vList);
  normalize_scalar(&(vList->var),hide,priority,colors,&x,&y,&z,&c);
  for(int i=0;i<1000;i++) {
  //  cout << x.a[i] << " " << y.a[i] << " " << z.a[i] << " " << c.a[i] << endl;
  }
  //normalize_vector(&(vList->var),vect_num,&ex,&ey,&ez);
  //pass math gl data to plot
  //vList->print();
  for(int i=0;i<equations->size();i++) {
    delete[] eqs[i];
  }
  delete[] eqs;
  return 1;
}
