#include "trackpiece.h"

TrackPiece::TrackPiece(float _x, float _y, float _z, float _width, 
			float _endWidth, float _length, float _roll, float _pitch, float _yaw){

	trackHeight = .2;
	x = _x;
	y = _y;
	z = _z;
	width = _width;
	endWidth = _endWidth;
	length = _length;
	roll = _roll;
	pitch = _pitch;
	yaw = _yaw;
	widthDiff = width - endWidth;

}	

void TrackPiece::draw(){	

	glPushMatrix();
	
	glTranslatef(x,y,z);
    glRotatef(yaw , 0,1,0);
    glRotatef(pitch, 1,0,0);
    glRotatef(roll, 0,0,1);
	//Top
	glBegin(GL_QUADS);
	glNormal3f( 0,+1, 0);
 	glVertex3f(x,y,z);
 	glVertex3f(x+width,y,z);
 	glVertex3f(x+endWidth,y,z-length);
 	glVertex3f(x+widthDiff,y,z-length);
 	glEnd();

 	//Bottom
 	glBegin(GL_QUADS);
 	glNormal3f( 0,-1, 0);
 	glVertex3f(x,y-trackHeight,z);
 	glVertex3f(x+width,y-trackHeight,z);
 	glVertex3f(x+endWidth,y-trackHeight,z-length);
 	glVertex3f(x+widthDiff,y-trackHeight,z-length);
 	glEnd();

 	//Left side
 	glBegin(GL_QUADS);
 	glNormal3f( -1,0, 0);
 	glVertex3f(x,y-trackHeight,z);
 	glVertex3f(x,y,z);
 	glVertex3f(x+widthDiff,y,z-length);
 	glVertex3f(x+widthDiff,y-trackHeight,z-length);
 	glEnd();

 	//Right side
 	glBegin(GL_QUADS);
 	glNormal3f(1,0, 0);
 	glVertex3f(x+width,y-trackHeight,z);
 	glVertex3f(x+width,y,z);
 	glVertex3f(x+endWidth,y,z-length);
 	glVertex3f(x+endWidth,y-trackHeight,z-length);
 	glEnd();


	glPopMatrix();
	
}