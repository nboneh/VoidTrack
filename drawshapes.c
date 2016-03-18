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

void drawCube()
{

  //  Offset, scale and rotate
  //  Enable textures
  //  Front
  glBegin(GL_QUADS);
  glNormal3f( 0, 0, 1);
  glTexCoord2f(0,0); glVertex3f(0,0, 1);
  glTexCoord2f(1,0); glVertex3f(1,0, 1);
  glTexCoord2f(1,1); glVertex3f(1,1, 1);
  glTexCoord2f(0,1); glVertex3f(0,1, 1);
  glEnd();
  //  Back
  glBegin(GL_QUADS);
  glNormal3f( 0, 0,-1);
  glTexCoord2f(0,0); glVertex3f(0,0,0);
  glTexCoord2f(1,0); glVertex3f(1,0,0);
  glTexCoord2f(1,1); glVertex3f(1,1,0);
  glTexCoord2f(0,1); glVertex3f(0,1,0);
  glEnd();
  //  Right
  glBegin(GL_QUADS);
  glNormal3f(1, 0, 0);
  glTexCoord2f(0,0); glVertex3f(1,0,0);
  glTexCoord2f(1,0); glVertex3f(1,1,0);
  glTexCoord2f(1,1); glVertex3f(1,1,1);
  glTexCoord2f(0,1); glVertex3f(1,0,1);
  glEnd();
  //  Left
  glBegin(GL_QUADS);
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0,0); glVertex3f(0,0,0);
  glTexCoord2f(1,0); glVertex3f(0,1,0);
  glTexCoord2f(1,1); glVertex3f(0,1,1);
  glTexCoord2f(0,1); glVertex3f(0,0,1);
  glEnd();
  //  Top
  glBegin(GL_QUADS);
  glNormal3f( 0,+1, 0);
  glTexCoord2f(0,0); glVertex3f(0,1,0);
  glTexCoord2f(1,0); glVertex3f(0,1,1);
  glTexCoord2f(1,1); glVertex3f(1,1,1);
  glTexCoord2f(0,1); glVertex3f(1,1,0);
  glEnd();
  //  Bottom
  glBegin(GL_QUADS);
  glNormal3f( 0,-1, 0);
  glTexCoord2f(0,0); glVertex3f(0,0,0);
  glTexCoord2f(1,0); glVertex3f(0,0,1);
  glTexCoord2f(1,1); glVertex3f(1,0,1);
  glTexCoord2f(0,1); glVertex3f(1,0,0);
  glEnd();
  //  Undo transformations and textures


}

