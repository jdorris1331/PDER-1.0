#ifndef GRAPHICS_H 
#define GRAPHICS_H


#include <mgl2/fltk.h>
#include "animation.h"
#include <mgl2/mgl.h>
#include <string>
#include "cont_data.h"
#include <time.h> 
class Graphics : public Animation 
{ 
	friend Animation;
        private:
		//The method that does calculating stuffz.
	public:
//		cont_data * calculator; //A pointer to the handy-dandy calculator.	
		void axis(double x = 0 , double  y =  0 , double z = 0, double ticks = 1);
		void calculation();
//		void calculation(int t, mglData* x, mglData* y, mglData * z, int n);
		void Run(){gr->Run();}
		void begin();
		//Graphics(){gr->zoom = true;}
		Graphics(cont_data * aCalculator){points = 100;  setCalculator(aCalculator);}
};
#endif //CTRLGRAPH_H 
