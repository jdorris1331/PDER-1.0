#include <math.h>
#include "ctrlsliders.h"

CtrlSliders::CtrlSliders(Graphics *myGraph, cont_data *myDat) : Fl_Pack(0, 0, 160, 30, 0)
{
    graph = myGraph;
	dat = myDat;
	
	std::vector<int> vCon;
	for (int i = 0; i < dat->vList->var.size(); i++)
	{
	  if (dat->vList->var[i].get_type() == 0) {
	    vCon.push_back(i); }
	}

	fraSliders[0] = new Fl_Pack(0, 0, 160, 30, 0);
	//fraSliders[0]->label("Constants");
	fraSliders[0]->align(FL_ALIGN_LEFT);
	fraSliders[0]->spacing(2);
	for (int i = 0; i < vCon.size(); i++)
	{	  
	  int diff = dat->vList->var[vCon[i]].show_max - dat->vList->var[vCon[i]].show_min;
	  double scl;
      if (diff != 0) { scl = 100/diff; }
	  else { scl = 100.0; }
	  if (scl == 0) { scl = 1.0; }
	  int prc;
	  for (prc = 0; prc < 10 && scl/pow(10, prc) > 1 ; prc++) {}
	  
	  if (dat->vList->var[vCon[i]].show_min < -99999 || dat->vList->var[vCon[i]].show_min > 99999) {
	    dat->vList->var[vCon[i]].show_min = dat->vList->var[vCon[i]].val; }
      if (dat->vList->var[vCon[i]].show_max > 99999 || dat->vList->var[vCon[i]].show_max < -99999) {
	    dat->vList->var[vCon[i]].show_max = dat->vList->var[vCon[i]].val; }
	
	  int min = dat->vList->var[vCon[i]].show_min * scl;
	  int max = dat->vList->var[vCon[i]].show_max * scl;
	  int init = dat->vList->var[vCon[i]].val * scl;
	  
	  new SliderBox(vCon[i], dat->vList->var[vCon[i]].name, min, max, init, scl, prc);
	}

	/*SliderBox *slidersN[] = { omega, theta_BA, theta_BP,
		D_BAM, D_BPM, theta_C, T_BA, T_BC,
		T_BAM, T_BPM };
	for (int ct = 0; ct < 10; ct++) {
		fraSliders[0]->add(slidersN[ct]);
	}*/

	fraSliders[0]->end();

	this->resizable(fraSliders[0]);
}
