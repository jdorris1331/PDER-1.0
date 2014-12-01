CC = clang++ -std=c++11 -lpthread
CFLAGS =  $(MATHGLI) $(GSLI) $(FLTKI) $(HEADERS)
#INCLUDES
HEADERS = -I ../include
OSLIBS = ../OSlibs
MATHGLI = -I$(OSLIBS)/mathgl/2.2.2.1/include
GSLI = -I$(OSLIBS)/gsl/1.16/include
FLTKI = -I$(OSLIBS)/fltk/1.3.2_1/include
#LIBS
AL = -L../lib -lanimation
MATHGLL = -L$(OSLIBS)/MathGL/2.2.2.1/lib -lmgl -lmgl-fltk
FLTKLL = -L$(OSLIBS)/fltk/1.3.2_1/lib -lfltk



LIBS = $(AL) $(MATHGLL)  $(FLTKLL)
EXECUTABLES = example1 example2

all: $(EXECUTABLES)



example2: 	example2.o
	$(CC) $(CFLAGS) -o $@ $^  $(LIBS)
example1:	example1.o 
	$(CC) $(CFLAGS) -o $@ $^  $(LIBS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@ 


clean: 
	rm *.o





