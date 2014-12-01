#include<iostream> 
#include "graphics.h"
#include "initview.h"
#include<thread>
int main()
{
	InitView init;
	init.show();
	return(Fl::run());
}
