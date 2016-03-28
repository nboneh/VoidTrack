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
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <GL/glut.h>
#include <AL/al.h>
#include <AL/alc.h>
#endif

#define PI 3.1415926
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))
#define Tan(th) tan(3.1415926/180*(th))
#define Cot(th) cot(3.1415926/180*(th))
#define ToRad(th) (3.1415926/180) * th

#define invCos(th) acos(th) *(180/3.1415926)
#define invSin(th) asin(th) *(180/3.1415926)
#define invTan(th) atan(th) *(180/3.1415926)

#define VELOCITY_ARRAY 4
#define DURATION_ARRAY  5

#define SHIFTS 7
#define LEN_REL_TO_TRACK 8

#define BOT_LEFT 0
#define BOT_RIGHT 1
#define TOP_RIGHT 2
#define TOP_LEFT 3

static const char* Shader_Attribs_Flame[] = {"","","","","Vel","DurationTime", NULL};
static const char* Shader_Attribs_Track[] = { "","","","","","","","Shifts", "lenRelToTrack", NULL};



#ifdef __cplusplus
extern "C" {
#endif

extern int SIMPLE_LIGHTING_SHADER;
extern  unsigned int BACKGROUND_TEXTURE;
extern int FLAME_SHADER;
extern unsigned int CLICK_ON_SOUND;
extern unsigned int CLICK_OFF_SOUND;
extern unsigned int JUMP_SOUND;

void Print(const char* format , ...);
void Fatal(const char* format , ...);
void Log(const char * format, ...);
unsigned int  LoadTexBMP(const char* file);
void Project(double fov,double asp,double dim);
void ErrCheck(const char* where);
float frand(float rng,float off);
char* ReadText(const char *file);
void PrintShaderLog(int obj,const char* file);
void PrintProgramLog(int obj);
void CreateShader(int prog,const GLenum type,const char* file);
int CreateShaderProg(const char* VertFile,const char* FragFile, char ** arrayAttributes);

float areaOfTrianlge(float x1,float y1,float x2,float y2,float x3,float y3);

void drawBall();
void drawCube(float width, float length, float height);
void drawRightAngleTrianlgePrism(float width, float length, float height, int deactiveCorner);

void setupOpenAl();

unsigned int loadSoundFile(const char *file);
void playSound(unsigned int alSource, bool loop);
#ifdef __cplusplus
}


#endif

#endif
