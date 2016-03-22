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
#define Tan(th) tan(3.1415926/180*(th))
#define invCos(th) acos(th) *(180/3.1415926)



#ifdef __cplusplus
extern "C" {
#endif



void Print(const char* format , ...);
void Fatal(const char* format , ...);
unsigned int  LoadTexBMP(const char* file);
void Project(double fov,double asp,double dim);
void ErrCheck(const char* where);
void PlaySound(const char* soundname);
float frand(float rng,float off);
char* ReadText(const char *file);
void PrintShaderLog(int obj,const char* file);
void PrintProgramLog(int obj);
void CreateShader(int prog,const GLenum type,const char* file);
int CreateShaderProg(const char* VertFile,const char* FragFile);
int CreateShaderProgParticle(const char* VertFile,const char* FragFile, char ** arrayAttributes);
float areaOfTrianlge(float x1,float y1,float x2,float y2,float x3,float y3);

void drawBall();
void drawCube();
#ifdef __cplusplus
}


#endif

#endif
