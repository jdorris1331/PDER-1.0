#include "animation.h"

Animation::Animation(std::string title, int s, int p){	
	gr = new mglFLTK(title.c_str()); //Create a Window
				  //Default Title.
	gr->ToggleZoom(); //Allow toggle by mouse.
	speed = s;	//SetDefault amount of speed.
	points = 100;  //Set Default amount of points.
	animation_paused = false;
	animation_begin = false;
	gr->Rotate(60,50); 
	gr->Box();
	gr->SetRanges(-points, points, -points, points, -points, points);
}

void Animation::rotate(int arg1,int  arg2)
{
	animation_paused = true;
	gr->Rotate(arg1, arg2);
	gr->Update();
}

void Animation::RunThread()
{
	std::thread graphThread(&Animation::Run, this);
	graphThread.detach();
}

void Animation::Run(){
	if(gr){
		gr->Run();
	}
}

Animation::~Animation(){
	if(gr){
		free(gr);
	}
}

void Animation::drawDots(mglData*  x, mglData *  y ,mglData *  z, mglData *c)
{
	gr->Clf(); //Clear the old graph.
	gr->Box();
//	gr->Dots(*x, *y, *z, *c);	
	//gr->Dots(*x, *y, *z, *x, *c);	
	gr->Tens(*x,*y,*z,*c, " .");
	gr->SetRanges(-points, points, -points, points, -points, points);
	gr->Update();
}

void Animation::UpdatePointers(int t, mglData* & x, mglData* & y, mglData* & z)
{
	//Update size fo points
	mglData* tx = new mglData((t+1)*points);
	mglData* ty = new mglData((t+1)*points);
	mglData* tz = new mglData((t+1)*points);
	if(x && y && z){		
		//Update size of pointers.
		tx = new mglData((t+1)*points);
		ty = new mglData((t+1)*points);
		tz = new mglData((t+1)*points);
				
		//memcpy old ponter into new pointer		
		memcpy(tx->a, x->a, (t)*points*sizeof(mreal));
		memcpy(ty->a, y->a, (t)*points*sizeof(mreal));
		memcpy(tz->a, z->a, (t)*points*sizeof(mreal));
		delete x; delete y; delete z; //Delete Old memory.
		x = tx; y = ty; z = tz;
	}
	else{
		x = new mglData(points);
		y = new mglData(points);
		z = new mglData(points);
	}
}

/*
void Animation::beginAnimation(){
	mglData *px = NULL, *py = NULL, *pz = NULL;
	mglData ex , ey , ez;
	int n = 20;
	ex.Create(n,n,n); ey.Create(n,n,n); ez.Create(n,n,n);
	int i, j,k;
	mreal  x,y,z, r1, r2;
	int i0;
	for(int t = 0; t < points; t++)
	{
		while(animation_paused == true)
		{
			std::this_thread::yield();
			drawDots(px,py,pz);	

		}
				
		UpdatePointers(t, px, py, pz);
		if(t == 0){
			calculation(t, px, py, pz, 0);			
		}
		else{
			calculation(t, px, py, pz, t*points);			
		}
	//		drawDots(px, py, pz);
	  for(i=0;i<n;i++)  for(j=0;j<n;j++)  for(k=0;k<n;k++)
  	{
    		x=2*i/(n-1.)-1; y=2*j/(n-1.)-1; z=2*k/(n-1.)-1; 
		i0 = i+n*(j+k*n);
    		r1 = pow(x*x+y*y+(z-0.3)*(z-0.3)+0.03,1.5);
    		r2 = pow(x*x+y*y+(z+0.3)*(z+0.3)+0.03,1.5);
    		ex.a[i0]=0.2*x/r1 - 0.2*x/r2;
    		ey.a[i0]=0.2*y/r1 - 0.2*y/r2;
    		ez.a[i0]=0.2*(z-0.3)/r1 - 0.2*(z+0.3)/r2;
  	}	
		gr->Vect3(ex,ey,ez);
	}
}
*/

void Animation::beginAnimation(){
	while(1)	
	{
		std::cout << "Called solve\n" << std::endl;
		calculator->solve();
		std::cout << "solve done\n" << std::endl;
		std::this_thread::yield();
		while(animation_paused == true)
		{
			std::this_thread::yield();
			gr->Update();	
		}
		if(calculator->vect_num == -1)
		{
		
		std::cout << "Called dots\n" << std::endl;
			drawDots(&calculator->x, &calculator->y, &calculator->z, &calculator->c);
		std::cout << "solve dots\n" << std::endl;
		}

	}
}

void Animation::toggleAnimation(){
	std::cout << "called toggle animan\n";
	if(animation_begin == false)
	{
		animation_paused = false;
		animation_begin = true;
		std::thread animation (&Animation::beginAnimation, this);
		animation.detach();
		//gr->Run();
	}
	else
		animation_paused = !animation_paused;
	std::cout << "Calling\n" << std::endl;
}


void Animation::update(){
	if(!animation_paused){
		if(gr)
		{
			gr->Update();
			std::cerr <<"updating graph\n";	
		}
		else
			std::cerr <<"Graph not read\n";
	}
}


