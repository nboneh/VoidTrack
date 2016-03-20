#include "spaceship.h"

SpaceShip::SpaceShip(){
	accelerationRate = 20;

	maxAddRoll = 40;
	rollRate = 50;

	maxAddPitch = 70;
	pitchRate = 50;

	centerX = .5;
	centerY = 0;
	centerZ = -.33; 

	floatingHeight = .4;

 	flame = new Flame();
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
	terminalVelocity = 20;
	velocity = 0;
	addRoll = 0;
	turn = 0;
	falling = false;
	addPitch = 0;
	fallingRate = 0;
	addY = 0;
}

void SpaceShip::go(){
	accelerating = true;
	addY = 0;
	roll = 0;
}


void SpaceShip::update(double t){
	if(!accelerating){
		floatingMotion(t);
	} else {
		flame->update(t, velocity);
		velocity += accelerationRate *t;
		if(velocity >= terminalVelocity)
			velocity = terminalVelocity;
	 	x -=  velocity*(Cos(pitch)*Sin(yaw)) *t;
      	y +=  velocity*(Sin(pitch)) *t;
     	z -=  velocity*(Cos(pitch)*Cos(yaw)) *t;
		
     	if(turn != 0){	
			yaw +=  t * addRoll;
			if(fabs(addRoll) < maxAddRoll){
				addRoll +=  turn * t * rollRate;
				 if(fabs(addRoll) >= maxAddRoll){
					addRoll = maxAddRoll * turn;
				}	
			}			
     	} else if(turn == 0 && addRoll != 0) {
     		yaw +=  t * addRoll ;
     		if(addRoll < 0){
     			addRoll +=  t * rollRate * 3;
     			if(addRoll >= 0)
     				addRoll = 0;
     		} else {
     			addRoll -=  t * rollRate * 3;
     			if(addRoll <= 0)
     				addRoll = 0;
     		}
     	}

     	if(falling){
			if(addPitch < maxAddPitch){
				addPitch +=   t * pitchRate;
				 if(addPitch >= maxAddPitch){
					addPitch = maxAddPitch;
				}	
			}
			fallingRate += t*60;
			y -= t*fallingRate;
		}
	} 
}

void SpaceShip::floatingMotion(double t){
	//For when the ships isn't moving
	floatingMotionCounter += t*3;
	addY = sin(floatingMotionCounter*2)*.05;
	roll = sin(floatingMotionCounter)*5;
}

void SpaceShip::draw(){
	glPushMatrix();
	
	glTranslatef(x,y + floatingHeight + addY,z);

    glTranslatef(centerX,centerY,centerZ);
    glRotatef(yaw+ addRoll/3 , 0,1,0);
    glRotatef(pitch - addPitch, 1,0,0);
    glRotatef(roll+addRoll, 0,0,1);
	glTranslatef(-centerX,-centerY,-centerZ);

	if(accelerating){
		glPushMatrix();
		glTranslatef(centerX,0,0);
		glRotatef(90,1,0,0);
		glScalef(1.5,1,1.5);
  		flame->draw();
   		glPopMatrix();
    }
    


	glColor3f(0,1,1);
	glBegin(GL_POLYGON);
    glVertex3f(0,0, 0);
    glVertex3f(.5,0, -1);
    glVertex3f(1,0, 0);
    glEnd();

    glColor3f(0,1,0);
	glBegin(GL_POLYGON);
    glVertex3f(.34,.01, -.7);
    glVertex3f(.5,.01, -1);
    glVertex3f(.66,.01, -.7);
    glEnd();


	glPopMatrix();

}

void SpaceShip::turnLeft(){
	if(turn == 1)
		return;
	turn = -1;
}

void SpaceShip::stopTurnLeft(){
	if(turn != -1)
		return;
	turn = 0;
}

void SpaceShip::turnRight(){
	if(turn == -1)
		return;
	turn = 1;
}

void SpaceShip::stopTurnRight(){
	if(turn != 1)
		return;
	turn =  0;
}

void SpaceShip::setRoll(float _roll){
	roll = _roll;
}

void SpaceShip::setPitch(float _pitch){
	pitch = _pitch;
}


float SpaceShip::getX(){
	return x + centerX;
}

float SpaceShip::getY(){
	return y;
}

float SpaceShip::getZ(){
	return z + centerZ;
}

float SpaceShip::getYaw(){
	return yaw ;
}

float SpaceShip::getPitch(){
	return pitch;
}

void SpaceShip::setFalling(){
	falling = true;
}



