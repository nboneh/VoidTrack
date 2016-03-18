#ifndef VoidTrack
#define VoidTrack

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))
#define PI 3.14159265



#ifdef __cplusplus
extern "C" {
#endif


extern unsigned int BACKGROUND;

void Print(const char* format , ...);
void Fatal(const char* format , ...);
unsigned int  LoadTexBMP(const char* file);
void Project(double fov,double asp,double dim);
void ErrCheck(const char* where);
void PlaySound(const char* soundname);

void drawBall();
void drawCube();
#ifdef __cplusplus
}


#endif

#endif
