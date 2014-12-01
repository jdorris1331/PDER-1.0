#ifndef ANIMATION_H 
#define ANIMATION_H
#include <mgl2/fltk.h>
#include <mgl2/mgl.h>
#include <mgl2/type.h>
#include <vector>
#include <unistd.h>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include "cont_data.h"
/*-------------------------------------------------------------------------
Author: Joey Allen
Created/last Modified: 10/5/14

Description:
The class animation controls the internal mechanisms of displaying and controlling
the speed of animation.
---------------------------------------------------------------------------*/
class Animation
{
	protected:
		mglFLTK* gr;
		cont_data* calculator;
		void Run();
		bool animation_paused; 
		int points;  //The amount of point to calculate.
	private:
		int speed; //The speed of the animation 
			   //**specificationf or speed not yet defined.
		//SIGNALS
		//If set to true, then animation will start/resume/continue
		//If set to false, animation will stall/pause until animation_paused is 
		//set to 1.
		bool animation_begin;
		//If set to false, then animation has not started. 
		//This function will be set to 1 when ToggleAnimation is started for hte 
		//first time.
		void beginAnimation(); //Begin animation will begin the calculation.
		void UpdatePointers(int t, mglData* &, mglData* & , mglData* & );
		//Internal Method used for updating memory for drawing.  Should never
		//Be called or used by functions other than beginAnimation();
	public:
		 Animation(std::string = "PDE SOLVER", int s = 1, int p = 5000);
		~Animation();

	//	virtual void calculation(){}  //I don't know what to do right here.
		//Theoretically this will be the method that controls the calculation 
		//Basic High-level animation controls.
//		virtual void calculation(int t, mglData* x, mglData * y, mglData * z, int n){}
		virtual void calculation(){}
		void toggleAnimation(); //Toggles animation from paused to resuming.	
					//First call to toggle will begin the animation.
		//Getters
		int getSpeed(){return(speed);}
		int getPoints(){return(points);}	
		//Setters
		int setCalculator(cont_data *aCalculator){calculator = aCalculator;}
		void RunThread();
		void setSpeed(int s){speed = s;}
		void setPoints(int p){points = p;}
		void update();
		void drawDots(mglData * , mglData* , mglData* , mglData*);
		void rotate(int arg1, int arg2);
};

#endif //ANIMATION_H
