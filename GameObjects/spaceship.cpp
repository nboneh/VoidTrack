#include "spaceship.h"

SpaceShip::SpaceShip(){
	accelerationRate = .1;
	reset();
}

void SpaceShip::reset(){
	x = 0;
	y = 0;
	z = 0;
	roll = 0;
	pitch = 0;
	yaw = 0;
	accelerating = false;
	floatingMotionCounter = 0;
	terminalVelocity = 1;
	velocity = 0;
	yaw = 40;
	//pitch = 45;
}

void SpaceShip::update(double t){
	if(!accelerating){
		floatingMotion(t);
	} else {
		velocity += accelerationRate *t;
		if(velocity >= terminalVelocity)
			velocity = terminalVelocity;
	  x +=  velocity*(cos(pitch)*sin(yaw));
      y += 	velocity*(sin(pitch));
      z +=  velocity*(cos(pitch)*cos(yaw));
	}
}

void SpaceShip::go(){
	accelerating = true;
	y = 0;
	roll = 0;
}

void SpaceShip::floatingMotion(double t){
	//For when the ships isn't moving
	floatingMotionCounter += t*3;
	y = sin(floatingMotionCounter*2)/30;
	roll = sin(floatingMotionCounter)*5;
}

void SpaceShip::draw(){
	glColor3f(0,1,1);
	glPushMatrix();
	glTranslatef(.5,0,-.3);
	glRotatef(roll, 0,0,1);
	glRotatef(yaw, 0,1,0);
	glRotatef(pitch, 1,0,0);
	glTranslatef(-.5,0,.3);
	glTranslatef(x,y,z);

	glBegin(GL_POLYGON);
    glVertex3f(0,0, 0);
    glVertex3f(.5,0, -1);
    glVertex3f(1,0, 0);
    glEnd();

	glPopMatrix();
}

void SpaceShip::setRoll(float _roll){
	roll = _roll;
}

void SpaceShip::setPitch(float _pitch){
	pitch = _pitch;
}

float SpaceShip::getX(){
	return x;
}

float SpaceShip::getY(){
	return y;
}

float SpaceShip::getZ(){
	return z;
}

float SpaceShip::getYaw(){
	return yaw;
}

float SpaceShip::getPitch(){
	return pitch;
}


