#include "VoidTrack.h"


static void Vertex(double th,double ph)
{
  double x = Sin(th)*Cos(ph);
  double y = Cos(th)*Cos(ph);
  double z =         Sin(ph);
  //  For a sphere at the origin, the position
  //  and normal vectors are the same
  glNormal3d(x,y,z);
  glTexCoord2f(th/360 ,(1-(ph+90)/180)); glVertex3d(x,y,z);
}

void drawCube(float width, float height ,float length)
{

 //Top
  glBegin(GL_QUADS);
  glNormal3f( 0,1, 0);
  glVertex3f(0,0,0);
  glVertex3f(width,0,0);
  glVertex3f(width,0,-length);
  glVertex3f(0,0,-length);
  glEnd();

  //Bottom
  glBegin(GL_QUADS);
  glNormal3f( 0,-1, 0);
  glVertex3f(0,-height,0);
  glVertex3f(width,-height,0);
  glVertex3f(width,-height,-length);
  glVertex3f(0,-height,-length);
  glEnd();

  //Left side
  glBegin(GL_QUADS);
  glNormal3f( -1,0, 0);
  glVertex3f(0,-height,0);
  glVertex3f(0,0,0);
  glVertex3f(0,0,-length);
  glVertex3f(0,-height,-length);
  glEnd();

  //Right side
  glBegin(GL_QUADS);
  glNormal3f(1,0, 0);
  glVertex3f(width,-height,0);
  glVertex3f(width,0,0);
  glVertex3f(width,0,-length);
  glVertex3f(width,-height,-length);
  glEnd();

  //Back
  glBegin(GL_QUADS);
  glNormal3f(0,0, 1);
  glVertex3f(0,0,0);
  glVertex3f(width,0,0);
  glVertex3f(width,-height,0);
  glVertex3f(0,-height,0);
  glEnd();

  //Front
  glBegin(GL_QUADS);
  glNormal3f(0,0, -1);
  glVertex3f(0,0,-length);
  glVertex3f(width,0,-length);
  glVertex3f(width,-height,-length);
  glVertex3f(0,-height,-length);
  glEnd();



  //  Undo transformations and textures


}
/*
*  Draw a ball
*     at (x,y,z)
*     radius (r)
*/
void drawBall()
{
  int inc       =  1;
  //  Bands of latitude
  int ph, th;
  for (ph=-90 ;ph<90;ph+=inc)
  {
     glBegin(GL_QUAD_STRIP);
     for (th=0;th<=360;th+=2*inc)
     {
        Vertex(th,ph);
        Vertex(th,ph+inc);
     }
     glEnd();
  }
}


void drawRightAngleTrianlgePrism(float width,float height, float length,  int deactiveCorner){
  switch(deactiveCorner){
    case BOT_LEFT:
              //Top
      glBegin(GL_POLYGON);
     glNormal3f( 0,1, 0);
     glVertex3f(width,0,0);
     glVertex3f(width,0,-length);
     glVertex3f(0,0,-length);
      glEnd();

      //Bot
     glBegin(GL_POLYGON);
     glNormal3f( 0,1, 0);
    glVertex3f(width,-height,0);
     glVertex3f(width,-height,-length);
     glVertex3f(0,-height,-length);
      glEnd();

     //Front
  glBegin(GL_QUADS);
  glNormal3f(0,0, -1);
  glVertex3f(0,0,-length);
  glVertex3f(width,0,-length);
  glVertex3f(width,-height,-length);
  glVertex3f(0,-height,-length);
  glEnd();

      //Right side
  glBegin(GL_QUADS);
  glNormal3f(1,0, 0);
  glVertex3f(width,-height,0);
  glVertex3f(width,0,0);
  glVertex3f(width,0,-length);
  glVertex3f(width,-height,-length);
  glEnd();



     //Cross
     glBegin(GL_QUADS);
     glNormal3f(-.707,0, .707);
     glVertex3f(width,0,0);
      glVertex3f(0,0,-length);
      glVertex3f(0,-height,-length);
     glVertex3f(width,-height,0);
     glEnd();
      break;
    case BOT_RIGHT:
            //Top
      glBegin(GL_POLYGON);
     glNormal3f( 0,1, 0);
     glVertex3f(0,0,0);
     glVertex3f(0,0,-length);
     glVertex3f(width,0,-length);
      glEnd();

      //Bot
     glBegin(GL_POLYGON);
     glNormal3f( 0,1, 0);
     glVertex3f(0,-height,0);
     glVertex3f(0,-height,-length);
     glVertex3f(width,-height,-length);
      glEnd();

     //Front
  glBegin(GL_QUADS);
  glNormal3f(0,0, -1);
  glVertex3f(0,0,-length);
  glVertex3f(width,0,-length);
  glVertex3f(width,-height,-length);
  glVertex3f(0,-height,-length);
  glEnd();

     //Left side
  glBegin(GL_QUADS);
  glNormal3f( -1,0, 0);
  glVertex3f(0,-height,0);
  glVertex3f(0,0,0);
  glVertex3f(0,0,-length);
  glVertex3f(0,-height,-length);
  glEnd();


     //Cross
     glBegin(GL_QUADS);
     glNormal3f(.707,0, .707);
      glVertex3f(0,0,0);
      glVertex3f(width,0,-length);
      glVertex3f(width,-height,-length);
     glVertex3f(0,-height,0);
     glEnd();
      break;
    case TOP_RIGHT:
             //Top
      glBegin(GL_POLYGON);
     glNormal3f( 0,1, 0);
     glVertex3f(width,0,0);
     glVertex3f(0,0,0);
     glVertex3f(0,0,-length);
      glEnd();

      //Bot
        glBegin(GL_POLYGON);
     glNormal3f( 0,-1, 0);
     glVertex3f(width,-height,0);
     glVertex3f(0,-height,0);
     glVertex3f(0,-height,-length);
      glEnd();

      //Back
       glBegin(GL_QUADS);
     glNormal3f(0,0, 1);
    glVertex3f(0,0,0);
    glVertex3f(width,0,0);
    glVertex3f(width,-height,0);
    glVertex3f(0,-height,0);
   glEnd();


     //Left side
  glBegin(GL_QUADS);
  glNormal3f( -1,0, 0);
  glVertex3f(0,-height,0);
  glVertex3f(0,0,0);
  glVertex3f(0,0,-length);
  glVertex3f(0,-height,-length);
  glEnd();


     //Cross
     glBegin(GL_QUADS);
     glNormal3f(.707,0, -.707);
      glVertex3f(width,0,0);
      glVertex3f(0,0,-length);
      glVertex3f(0,-height,-length);
     glVertex3f(width,-height,0);
     glEnd();
      break;
    case TOP_LEFT:
           //Top
      glBegin(GL_POLYGON);
     glNormal3f( 0,1, 0);
     glVertex3f(0,0,0);
     glVertex3f(width,0,0);
     glVertex3f(width,0,-length);
      glEnd();

      //Bot
        glBegin(GL_POLYGON);
     glNormal3f( 0,-1, 0);
     glVertex3f(0,-height,0);
     glVertex3f(width,-height,0);
     glVertex3f(width,-height,-length);
      glEnd();

      //Back
       glBegin(GL_QUADS);
     glNormal3f(0,0, 1);
    glVertex3f(0,0,0);
    glVertex3f(width,0,0);
    glVertex3f(width,-height,0);
    glVertex3f(0,-height,0);
   glEnd();


     //Right side
     glBegin(GL_QUADS);
     glNormal3f(1,0, 0);
      glVertex3f(width,-height,0);
      glVertex3f(width,0,0);
      glVertex3f(width,0,-length);
     glVertex3f(width,-height,-length);
     glEnd();


     //Cross
     glBegin(GL_QUADS);
     glNormal3f(-.707,0, -.707);
      glVertex3f(0,0,0);
      glVertex3f(width,0,-length);
      glVertex3f(width,-height,-length);
     glVertex3f(0,-height,0);
     glEnd();
      break;
  }
}
