#ifndef INITVIEW_H
#define INITVIEW_H

//#include <Windows.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Pack.H>
#include <vector>
#include <string>
#include "guiview.h"

class InitView : public Fl_Window
{
private:
	Fl_Button *btnOpen, *btnBrowse;
	Fl_Input *txtFile;
	std::vector<GUIView*> vGui;
	Fl_Pack *fraView, *fraBut;

	static void cb_pickFile(Fl_Widget *w, void *data);
	void pickFile();
	static void cb_launchControls(Fl_Widget *w, void *data);
	void launchControls();

public:
    InitView();
};

#endif // INITVIEW_H
