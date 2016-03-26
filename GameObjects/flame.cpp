#include "flame.h"


Flame::Flame(){
	numOfParticles = 1000;
	Vert  = new float[3*numOfParticles];
  Color = new float[3*numOfParticles];
  Vel   = new float[3*numOfParticles];
  DurationTime = new float[numOfParticles];
  reset();
}

void Flame::reset(){
  counter= 0;
  lastVelocity = 0; 
     //  Array Pointers
   float* vert  = Vert;
   float* vel   = Vel;
   float* durationTime = DurationTime;
   //  Loop over NxN patch
   for (int i=0;i<numOfParticles;i++){
    //  Location x,y,z
    float radius = frand(0.05, 0.0);
    float angle =  frand(M_PI*2,0.0 );
    *vert++ = radius * cos(angle);
    *vert++ = 0;
    *vert++ = radius * sin(angle);
    //  Velocity
    *vel++ = (radius * cos(angle)) * 10;
    *vel++ = 0;
    *vel++ = (radius * sin(angle)) *10;
    //  Launch time
    *durationTime++ = frand(0.05,0.01);
  }

}

void Flame::setColor(float r1,float g1,float b1, float r2, float g2, float b2){
    if(r1 > r2){
      highR = r1;
      lowR = r2;
    } else {
      highR = r2;
      lowR = r1;
    }

   if(g1 > g2){
      highG = g1;
      lowG = g2;
    } else {
      highG = g2;
      lowG = g1;
    }

    if(b1 > b2){
      highB = b1;
      lowB = b2;
    } else {
      highB = b2;
      lowB = b1;
    }

    float* color = Color;
     //  Loop over NxN patch
   for (int i=0;i<numOfParticles;i++){
    *color++ = frand(highR,lowR);
    *color++ = frand(highG,lowG);
    *color++ = frand(highB,lowB);
  
  }

}


void Flame::update(float t, float velocity){
  if(lastVelocity <= velocity){
     for (int i=1;i<numOfParticles;i+=3){
      Vel[i] += (velocity -lastVelocity);
     }
    lastVelocity = velocity;
  }
   glUseProgram(FLAME_SHADER);
	int loc;
	counter += t;
	loc = glGetUniformLocation(FLAME_SHADER, "time");
  if (loc>=0) glUniform1f(loc,counter);
  glUseProgram(0);
}

void Flame::draw(){
	 glUseProgram(FLAME_SHADER);
	glPointSize(2);
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
    glDrawArrays(GL_POINTS,0,numOfParticles);

    glDisable(GL_POINT_SPRITE);
    glDisable(GL_BLEND);
        //  Disable arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);

   glDisableVertexAttribArray(VELOCITY_ARRAY);
   glDisableVertexAttribArray(DURATION_ARRAY);
   	 glUseProgram(0);
}
