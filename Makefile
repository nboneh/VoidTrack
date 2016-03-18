# VoidTrack
EXE=VoidTrack

# Main target
all:  
	cd GameObjects; make; 
	@$(MAKE) --no-print-directory $(EXE)


#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall 
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm  -lssl -lrt -lcrypto -lpthread
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a .DS_Store; cd GameObjects; make clean
endif

# Dependencies
VoidTrack.o: VoidTrack.cpp 
fatal.o: fatal.c 
loadtexbmp.o: loadtexbmp.c 
print.o: print.c 
project.o: project.c 
errcheck.o: errcheck.c
drawshapes.o: drawshapes.c 
sound.o: sound.c

#  Create archive
VoidTrack.a: fatal.o loadtexbmp.o print.o project.o errcheck.o drawshapes.o sound.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
VoidTrack: VoidTrack.o GameObjects/GameObjects.a VoidTrack.a 
	g++ -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)
