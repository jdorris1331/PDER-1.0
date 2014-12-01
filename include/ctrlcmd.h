#ifndef CTRLCMD_H
#define CTRLCMD_H

//#include <Windows.h>
#include <Fl/Fl_Pack.H>

class CtrlCmd : public Fl_Pack
{
public:
    CtrlCmd();

private:
    Fl_Pack *fraCtrlCmd[3];
};

#endif // CTRLCMD_H
