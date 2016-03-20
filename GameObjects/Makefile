
all: GameObjects.a

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
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(archive) *.o *.a .DS_Store
endif

# Dependencies
background.o: background.cpp 
spaceship.o: spaceship.cpp 
flame.o: flame.cpp
track.o: track.cpp
trackpiece.o: trackpiece.cpp

GameObjects.a: background.o spaceship.o flame.o track.o trackpiece.o
	ar -rcs $@ $^


# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<


#  Clean
clean:
	$(CLEAN)
