#include "flame.h"

#define VELOCITY_ARRAY 4
#define DURATION_ARRAY    5
const char* Name[] = {"","","","","Vel","DurationTime", NULL};

Flame::Flame(){
	numOfParticles = 1000;
	Vert  = new float[3*numOfParticles];
  Color = new float[3*numOfParticles];
  Vel   = new float[3*numOfParticles];
  DurationTime = new float[numOfParticles];
  shader = CreateShaderProgParticle("shaders/flameshader.vert",NULL, (char **)Name);
  reset();
  init();
}

void Flame::reset(){
  counter= 0;
  highR = 1;
  lowR = .5;

  highG = .4;
  lowG = 0;

  highB = .4;
  lowB = 0;
  lastVelocity = 0;

}
void Flame::init(){
		   //  Array Pointers
   float* vert  = Vert;
   float* color = Color;
   float* vel   = Vel;
   float* durationTime = DurationTime;
   //  Loop over NxN patch
   for (int i=0;i<numOfParticles;i++){
    //  Location x,y,z
    float radius = frand(0.1, 0.0);
    float angle =  frand(M_PI*2,0.0 );
    *vert++ = radius * cos(angle);
    *vert++ = 0;
    *vert++ = radius * sin(angle);
    //  Color r,g,b (0.5-1.0)
    *color++ = frand(highR,lowR);
    *color++ = frand(highG,lowG);
    *color++ = frand(highB,lowB);
    //  Velocity
    *vel++ = (radius * cos(angle)) * frand(2.0, 0.0);
    *vel++ = frand(2.0, 0.0);
    *vel++ = (radius * sin(angle)) * frand(2.0, 0.0);
    //  Launch time
    *durationTime++ = frand(0.05,0.005);
  }
}

void Flame::update(float t, float velocity){
  if(lastVelocity <= velocity){
     for (int i=0;i<numOfParticles;i++){
      Vel[i*3 +1] += (velocity -lastVelocity);
     }
    lastVelocity = velocity;
  }
   glUseProgram(shader);
	int loc;
	counter += t;
	loc = glGetUniformLocation(shader, "time");
  if (loc>=0) glUniform1f(loc,counter);
  glUseProgram(0);
}

void Flame::draw(){
	 glUseProgram(shader);
	glPointSize(2.5);
	 //  Set particle size
   //  Point vertex location to local array Vert
   glVertexPointer(3,GL_FLOAT,0,Vert);
   //  Point color array to local array Color
   glColorPointer(3,GL_FLOAT,0,Color);
   //  Point attribute arrays to local arrays
   glVertexAttribPointer(VELOCITY_ARRAY,3,GL_FLOAT,GL_FALSE,0,Vel);
   glVertexAttribPointer(DURATION_ARRAY,1,GL_FLOAT,GL_FALSE,0,DurationTime);
   //  Enable arrays used by DrawArrays
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   glEnableVertexAttribArray(VELOCITY_ARRAY);
   glEnableVertexAttribArray(DURATION_ARRAY);
   //  Set transparent large particles
	glEnable(GL_POINT_SPRITE);
    glTexEnvi(GL_POINT_SPRITE,GL_COORD_REPLACE,GL_TRUE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glDepthMask(0);

    glDrawArrays(GL_POINTS,0,numOfParticles);

    glDisable(GL_POINT_SPRITE);
    glDisable(GL_BLEND);
     glDepthMask(1);
        //  Disable arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);

   glDisableVertexAttribArray(VELOCITY_ARRAY);
   glDisableVertexAttribArray(DURATION_ARRAY);
   	 glUseProgram(0);
}
