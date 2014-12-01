#include <mgl2/fltk.h>
#include <unistd.h>
int main(int argc,char **argv)
{
   mglPoint pnt;
  mglFLTK gr("test");     // create window
  gr.RunThr();            // run event loop in separate thread
  for(int i=0;i<10;i++)   // do calculation
  {
    sleep(1);             // which can be very long
    pnt = mglPoint(2*mgl_rnd()-1,2*mgl_rnd()-1);
    gr.Clf();             // make new drawing
    gr.Line(mglPoint(),pnt,"Ar2");
    char str[10] = "i=0"; str[2] = '0'+i;
    gr.Puts(mglPoint(),str);
    gr.Update();          // update window when you need it
  }
  return 0;   // finish calculations and close the window
}
