#ifndef CTRLGUI_H
#define CTRLGUI_H

//#include <Windows.h>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Button.H>
//#include <FL/Fl_Choice.H>
//#include <FL/Fl_Hor_Nice_Slider.H>
//#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Output.H>
//#include <FL/Fl_Input.H>
#include "graphics.h"
#include "SliderBox.h"

class CtrlGui : public Fl_Pack
{
private:
	Fl_Pack *fraCtrlGui[3], *fraRot;
	//Fl_Button *btnEdit, *btnDelete, *btnAdd, *btnSettings;
	//Fl_Choice *cmbAdd, *cmbUpdateFreq;
	//Fl_Hor_Nice_Slider *sldSpeed;
	//Fl_Check_Button *chkViewUpdates;

	Graphics* graph;
	Fl_Button *btnStart;
	Fl_Output *lblRot;
	//Fl_Input *txtRot;
	SliderBox *sldXRot, *sldYRot, *sldZRot;

	static void cb_toggleGraph(Fl_Widget *w, void *data);
	void toggleGraph();
	static void cb_rotateGraph(Fl_Widget *w, void *data);
	void rotateGraph();
	
	int togglekludge = 0;

public:
    CtrlGui(Graphics *myGraph);
};

#endif // CTRLGUI_H
