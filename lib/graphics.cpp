#include "graphics.h"
#include <unistd.h>
#include <iostream>
void Graphics::axis(double x, double y, double z, double ticks){
	
	gr->Axis();
	gr->Rotate(90,90);
	gr->Box();

}
/*
void Graphics::calculation(int t, mglData* x, mglData * y, mglData * z, int  n  ){
	int i, j,k;
	for(i = n; i < (n+100); i++) for(j = n; j < (n + 100); j++) for(k = n; k < (n + 100); k++)
	{
    		x->a[i] = .7*t*cos(.05*i)*cos(.05*i);
    		y->a[j] = 0.9*t*cos(.05*j)*sin(.05*j);
    		z->a[k] = 0.6*t*sin(.05*k)*sin(.05*k);
	}
}
*/


/*
void Graphics::calculation(){
//	gr->Alpha(true);
	register long i,j,k, n = 20, m = 20, l = 20, i0;
	a.Create(n,m,l);
	bool begin = true;
  for(i=0;i<n;i++)  for(j=0;j<m;j++)  for(k=0;k<l;k++)
  {
	std::cout << "i= " << i << "j= " << j << "k = " << k << std::endl;	
	while(animation_paused == true)
	{
		std::cout << "yielding thread\n";
		std::this_thread::yield();
		gr->Update();
		std::cout << "waking thread\n";
	}
    		x=2*i/(n-1.)-1; y=2*j/(m-1.)-1; z=2*k/(l-1.)-1; i0 = i+n*(j+m*k);
     	a.a[i0] = -2*(x*x + y*y + z*z*z*z - z*z - 0.1);
  	

	if(begin == true)
	{
		sleep(1);
		begin = false;	
	}
	//axis();	
	//gr->Plot(y, x, z);
		gr->Clf();
//       gr->Axis();
 //       gr->Rotate(90,90);
  //      gr->Box();
		gr->Box();
		gr->Surf3(a);
		//gr->Dens3(a);
		//gr->ContF(a);
//		gr->Axial(a);
		//gr->Surf3C(a);
			gr->Update();
  	//	update(); 
		
//	}
  }	
	gr->Rotate(50,60);
}

*/
void Graphics::calculation(){
	//solveFinished = false;
	calculator->solve();
	//solveFinished = true;

}

