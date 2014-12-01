#ifndef SPINNERBOX_H
#define SPINNERBOX_H

//#include <Windows.h>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Radio_Round_Button.H>
#include "sliderbox.h"
#include "model.h"

class SpinnerBox : public Fl_Pack
{
private:
	Fl_Pack *fraSpi[3], *fraBox[5];
	Fl_Output *lblName, *lblCrd, *lblVal, *txtVal;
	Fl_Input *txtColor, *txtCrd;
	Fl_Button *btnColor;
	Fl_Spinner *spnPos;
	Fl_Check_Button *chkVisible;
	Fl_Radio_Round_Button *radVisible;
	int count = 10;

	int pos;
	int vartype = 0;
	SliderBox *sldMin, *sldMax;
	int index;

	static void cb_setColor(Fl_Widget *w, void *data);
	void setColor();
	static void cb_changeColor(Fl_Widget *w, void *data);
	void changeColor();
	void updateColor(int r, int g, int b);
	static void cb_updatePos(Fl_Widget *w, void *data);
	void updatePos();
	static void cb_vectorExclusive(Fl_Widget *w, void *data);
	void vectorExclusive();
	static void cb_valAtCrd(Fl_Widget *w, void *data);
	void valAtCrd();

public:
    SpinnerBox(int ind, const char *name, const char *color, int position, int vt = 0);
	void setCount(int ct);
	int getPos();
	void setPos(int p);
	void changeWhen(uchar w);
	SpinnerBox *last, *next;
	void toggleVector();
	int getIndex();
};

#endif // SPINNERBOX_H
