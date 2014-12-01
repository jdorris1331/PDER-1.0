#include "ctrlgui.h"

void CtrlGui::cb_toggleGraph(Fl_Widget *w, void *data)
{
	((CtrlGui*)data)->toggleGraph();
}
void CtrlGui::toggleGraph()
{
	//std::cout << "calling toggle\n";

	if (togglekludge == 0) { togglekludge++; btnStart->label("Pause"); }
	
	graph->toggleAnimation();
	//sleep(1);
	//graph->Run();
	std::cout << btnStart->label() << std::endl;

	if (btnStart->label()[0] == 'S') { btnStart->label("Pause"); }
	else { btnStart->label("Start"); }
	if (togglekludge == 0) { togglekludge++; btnStart->label("Pause"); }

}

void CtrlGui::cb_rotateGraph(Fl_Widget *w, void *data) { ((CtrlGui*)data)->rotateGraph(); }
void CtrlGui::rotateGraph()
{
    int arg1, arg2;
	arg1 = sldXRot->sld->value();
	arg2 = sldYRot->sld->value();
	graph->rotate(arg1, arg2);
}

CtrlGui::CtrlGui(Graphics *myGraph) : Fl_Pack(0, 0, 900, 30, 0)
{
	graph = myGraph;

	this->type(Fl_Pack::HORIZONTAL);
	this->spacing(1);

    /*fraCtrlGui[0] = new Fl_Pack(0, 0, 900, 30, 0);
	fraCtrlGui[0]->type(Fl_Pack::HORIZONTAL);
	btnEdit = new Fl_Button(0, 0, 100, 30, "Edit");
	btnDelete = new Fl_Button(0, 0, 100, 30, "Delete");
	btnAdd = new Fl_Button(0, 0, 100, 30, "Add");
	cmbAdd = new Fl_Choice(0, 0, 100, 30, 0);
	Fl_Menu_Item cmbItems0[] = {
		{ "Button" },
		{ "Slider" },
		{ "Switch" },
		{ "Chooser" },
		{ "Input" },
		{ "Monitor" },
		{ "Plot" },
		{ "Output" },
		{ "Note" },
		{ 0 } };
	cmbAdd->copy(cmbItems0);
	fraCtrlGui[0]->end();*/

	fraCtrlGui[1] = new Fl_Pack(0, 0, 900, 30, 0);
	fraCtrlGui[1]->type(Fl_Pack::HORIZONTAL);
	btnStart = new Fl_Button(0, 0, 100, 30, 0);
	btnStart->label("Start");
	
	fraRot = new Fl_Pack(0, 0, 135, 22, 0);
	fraRot->type(Fl_Pack::HORIZONTAL);
	fraRot->box(FL_UP_FRAME);
	lblRot = new Fl_Output(6, 15, 75, 25, 0);
	lblRot->box(FL_NO_BOX);
	lblRot->insert("Rotation:");
	sldXRot = new SliderBox(-1, "x", 0, 359, 0, 1.0, 0, 90, 20);
	sldYRot = new SliderBox(-1, "y", 0, 359, 0, 1.0, 0, 90, 20);
	//sldZRot = new SliderBox(-1, "z", 0, 359, 0, 1.0, 0, 90, 20);
	fraRot->end();
	
	/*sldSpeed = new Fl_Hor_Nice_Slider(0, 0, 100, 10, "Speed");
	chkViewUpdates = new Fl_Check_Button(0, 0, 110, 30, "View Updates");
	cmbUpdateFreq = new Fl_Choice(0, 0, 100, 30, 0);
	Fl_Menu_Item cmbItems1[] = {
		{ "Continuous" },
		{ "On Tick" },
		{ 0 } };
	cmbUpdateFreq->copy(cmbItems1);*/
	fraCtrlGui[1]->end();

	/*fraCtrlGui[2] = new Fl_Pack(0, 0, 100, 30, 0);
	btnSettings = new Fl_Button(0, 0, 100, 30, "Settings");
    fraCtrlGui[2]->end();*/

	//this->resizable(fraCtrlGui[1]);
	//fraCtrlGui[1]->resizable(sldSpeed);

	btnStart->callback(cb_toggleGraph, this);
	sldXRot->sld->callback(cb_rotateGraph, this);
	sldYRot->sld->callback(cb_rotateGraph, this);
	//sldZRot->callback(cb_rotateGraph, this);
}
