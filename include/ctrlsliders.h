#ifndef CTRLSLIDERS_H
#define CTRLSLIDERS_H

//#include <Windows.h>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Scroll.H>
#include "graphics.h"
#include "sliderbox.h"
#include "MglWrapper/MglWrapper.h"
#include "cont_data.h"

class CtrlSliders : public Fl_Pack
{
private:
    MglWrapper *mgl;
    Fl_Pack *fraGraph, *fraSliders[5], *fraButtons[2];
	std::vector<SliderBox*> sliders;
			
	Graphics *graph;
	cont_data *dat;

public:
	CtrlSliders(Graphics *myGraph, cont_data *myDat);
	static void cb_sendPos(Fl_Widget *w, void *data);
	void sendPos();
};

#endif // CTRLSLIDERS_H
