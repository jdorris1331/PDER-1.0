#ifndef GUIVIEW_H
#define GUIVIEW_H

//#include <Windows.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Pack.H>
//#include <FL/Fl_Scroll.H>
#include "ctrlmenubar.h"
#include "graphics.h"
#include "cont_data.h"

class GUIView : public Fl_Window
{
private:
	CtrlMenuBar *mb;
	Fl_Pack *fraFrame, *fraMain[3];

	Graphics *graph;
	static void cb_launchGraph(Fl_Widget *w, void *data);
	void launchGraph();
	
	cont_data *dat;

public:
    GUIView(const char *sFile);
};

#endif // GUIVIEW_H
