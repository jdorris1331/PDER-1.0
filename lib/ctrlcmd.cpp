#include "ctrlcmd.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>

Fl_Output *lblCommandCenter, *lblObserver;
Fl_Text_Display *txtLog;
Fl_Button *btnSwitch, *btnClear, *btnHistory;
Fl_Input *txtCmd;

CtrlCmd::CtrlCmd() : Fl_Pack(0, 0, 900, 30, 0)
{
    this->spacing(1);

	fraCtrlCmd[0] = new Fl_Pack(0, 0, 900, 30, 0);
    fraCtrlCmd[0]->type(Fl_Pack::HORIZONTAL);
	lblCommandCenter = new Fl_Output(0, 0, 120, 30, 0);
	lblCommandCenter->box(FL_NO_BOX);
	lblCommandCenter->insert(" Command Center");
	btnSwitch = new Fl_Button(0, 0, 30, 30, 0);
    btnClear = new Fl_Button(0, 0, 100, 30, "Clear");
	fraCtrlCmd[0]->end();

	fraCtrlCmd[1] = new Fl_Pack(0, 0, 900, 30, 0);
	fraCtrlCmd[1]->type(Fl_Pack::HORIZONTAL);
	txtLog = new Fl_Text_Display(0, 0, 900, 60, 0);
	fraCtrlCmd[1]->resizable(txtLog);
	fraCtrlCmd[1]->end();

	fraCtrlCmd[2] = new Fl_Pack(0, 0, 900, 30, 0);
	fraCtrlCmd[2]->type(Fl_Pack::HORIZONTAL);
	lblObserver = new Fl_Output(0, 0, 80, 30, 0);
	lblObserver->box(FL_NO_BOX);
	lblObserver->insert(" observer>");
	txtCmd = new Fl_Input(0, 0, 790, 30, 0);
	btnHistory = new Fl_Button(0, 0, 30, 30, 0);
	fraCtrlCmd[2]->resizable(txtCmd);
	fraCtrlCmd[2]->end();

	//this->resizable(fraCtrlCmd[1]);
	//this->end();
}
