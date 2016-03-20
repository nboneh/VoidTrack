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
	glNormal3f( 0,1, 0);
 	glVertex3f(0,0,0);
 	glVertex3f(width,0,0);
 	glVertex3f(endWidth,0,-length);
 	glVertex3f(widthDiff,0,-length);
 	glEnd();

 	//Bottom
 	glBegin(GL_QUADS);
 	glNormal3f( 0,-1, 0);
 	glVertex3f(0,-trackHeight,0);
 	glVertex3f(width,-trackHeight,0);
 	glVertex3f(endWidth,-trackHeight,-length);
 	glVertex3f(widthDiff,-trackHeight,-length);
 	glEnd();

 	//Left side
 	glBegin(GL_QUADS);
 	glNormal3f( -1,0, 0);
 	glVertex3f(0,-trackHeight,0);
 	glVertex3f(0,0,0);
 	glVertex3f(widthDiff,0,-length);
 	glVertex3f(widthDiff,-trackHeight,-length);
 	glEnd();

 	//Right side
 	glBegin(GL_QUADS);
 	glNormal3f(1,0, 0);
 	glVertex3f(width,-trackHeight,0);
 	glVertex3f(width,0,0);
 	glVertex3f(endWidth,0,-length);
 	glVertex3f(endWidth,-trackHeight,-length);
 	glEnd();


	glPopMatrix();
	
}