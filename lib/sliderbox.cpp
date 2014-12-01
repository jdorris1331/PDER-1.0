#include "sliderbox.h"
#include <iomanip>

int SliderBox::getIndex() { return index; }

void SliderBox::cb_update(Fl_Widget *w, void *data) { ((SliderBox*)data)->update(); }
void SliderBox::update()
{
	dblVal = sld->value() / dblScl;
	ss.clear();
	ss.str("");
	ss << std::fixed << std::setprecision(iPrc) << dblVal;
	sVal = ss.str();
	lblVal->label(sVal.c_str());
	this->redraw();
}

SliderBox::SliderBox(int ind, const char *name, int min, int max, int val, double scl, int prc, int w, int h) : Fl_Pack(0, 0, w, h, 0)
{
    index = ind;
    iPrc = prc;
    dblScl = scl;
    dblVal = val/scl;
    ss.clear();
    ss.str("");
    ss << std::fixed << std::setprecision(prc) << dblVal;
    sVal = ss.str();

	this->box(FL_UP_FRAME);
	/*if (w == 160 && h == 35)
	{ 
		this->color(fl_rgb_color(200, 200, 200));
		this->redraw();
	}*/

	fraSli[0] = new Fl_Pack(0, 0, w, 20 *h / 35, 0);
	fraSli[0]->type(Fl_Pack::HORIZONTAL);
	lblName = new Fl_Output(6, 15, 155 * w / 160, 20 * h / 35, 0);
	lblName->box(FL_NO_BOX);
	lblName->insert(name);
	lblVal = new Fl_Output(105, 15, 50 * w / 160, 20 * h / 35, 0);
	lblVal->box(FL_NO_BOX);
	lblVal->label(sVal.c_str());
	fraSli[0]->end();

	fraSli[1] = new Fl_Pack(0, 0, w, 20 * h / 35, 0);
	fraSli[1]->type(Fl_Pack::HORIZONTAL);
	sld = new Fl_Hor_Nice_Slider(5, 1, 155 * w / 160, 20 * h / 35, 0);
	sld->bounds(min, max);
	sld->value(val);
	fraSli[1]->end();

	sld->callback(cb_update, this);
	this->end();
}
