CC = clang++ -std=c++11


#include Includes
HEADERS = -I../include
OSLIBS = ../OSlibs
MATHGLI = -I$(OSLIBS)/mathgl/2.2.2.1/include 
GSLI = -I$(OSLIBS)/gsl/1.16/include
FLTKI = -I$(OSLIBS)/fltk/1.3.2_1/include


#Linked Libs
MATHGLL = -L$(OSLIBS)/MathGL/2.2.2.1/lib -lmgl -lmgl-fltk
FLTKLL = -L$(OSLIBS)/fltk/1.3.2_1/lib -lfltk

LIBS = -L../lib -l $(MATHGLL) $(FLTKLL)
CFLAGS = -Wall $(HEADERS) $(MATHGLI) $(GSLI) $(FLTKI) 
AR = ar
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(notdir $(CPP_FILES:.cpp=.o))

.PHONY: all clean

all: libanimation.a

libanimation.a: $(OBJ_FILES)
	$(AR) rvu $@ $(OBJ_FILES)
	ranlib $@


%.o: %.cpp
	$(CC) -c $(CFLAGS)  $< -o $@

clean:
	rm -f *.o libanimation.a





