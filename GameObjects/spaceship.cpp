#include "spaceship.h"

SpaceShip::SpaceShip(){
	accelerationRate = 5;

	updateRate = 100;

	maxAddRoll = 40;
	rollRate = 50;

	centerX = .5;
	centerY = 0;
	centerZ = -.33; 

	floatingHeight = .4;
	maxStrecth = .3;

	stretchRate = 3;

 	flame = new Flame();
	reset();
}

void SpaceShip::reset(){
	x = 0;
	y = 0;
	z = -.5;
	roll = 0;
	pitch = 0;
	yaw = 0;
	accelerating = false;
	floatingMotionCounter = 0;
	terminalVelocity = 10;
	velocity = 0;
	addRoll = 0;
	turn = 0;
	fallingRate = 0;
	floatingY = 0;
	updatePitch = 0;
	updateRoll = 0;
	stretching = 0;
	addStrecth =0;
	jumped = false;
}

void SpaceShip::go(){
	accelerating = true;
	floatingY = 0;
	roll = 0;
}


void SpaceShip::update(double t){
	if(!accelerating){
		floatingMotion(t);
	} else {
		velocity += accelerationRate *t;
		if(velocity >= terminalVelocity)
			velocity = terminalVelocity;
		
		flame->update(t, velocity);
		
	 	x -=  velocity*(Cos(pitch )*Sin(yaw)) *t;
      	y +=  velocity*(Sin(pitch)) *t;
     	z -=  velocity*(Cos(pitch)*Cos(yaw)) *t;
		
		updateValues(t);
    	updateTurning(t);
		updateFalling(t);
		if(stretching != 0)
			updateStretch(t);
	} 
}
void SpaceShip::updateStretch(double t){
	addStrecth += stretching * stretchRate * t;
	if(addStrecth >= maxStrecth){
		stretching = -1;
		if(!jumped)
			startJump();
	}
	if(addStrecth <= 0){
		addStrecth = 0;
		stretching = 0;
	   	jumped = !jumped;
	}
}

void SpaceShip::floatingMotion(double t){
	//For when the ships isn't moving
	floatingMotionCounter += t*3;
	floatingY = sin(floatingMotionCounter*2)*.05;
	roll = sin(floatingMotionCounter)*5;
}

void SpaceShip::updateTurning(double t){
	if(turn != 0){	
		yaw +=  t * Cos(roll)*addRoll;
			if(fabs(addRoll) < maxAddRoll){
				addRoll +=  turn * t * rollRate;
				 if(fabs(addRoll) >= maxAddRoll){
					addRoll = maxAddRoll * turn;
				}	
			}			
    } 
    else if(turn == 0 && addRoll != 0) {
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

}

void SpaceShip::updateFalling(double t){
	fallingRate += t*4.9;
	x += fallingRate*(Sin(roll)) *t;
    y -=  fallingRate*(Cos(pitch)*Cos(roll))*t;
    z -=  fallingRate*(Sin(pitch)) *t;
		
}

void SpaceShip::updateValues(double t){
	if(roll < updateRoll){
     	roll += t*updateRate;
     	if(roll >= updateRoll)
     		roll = updateRoll;
    } else if (roll > updateRoll){
    	roll -= t*updateRate;
     	if(roll <= updateRoll)
     		roll = updateRoll;
    }

    if(pitch < updatePitch){
     	pitch += t*updateRate;
     	if(pitch >= updatePitch)
     		pitch = updatePitch;
    } else if (pitch > updatePitch){
    	pitch -= t*updateRate;
     	if(pitch <= updatePitch)
     		pitch = updatePitch;
    }
}

void SpaceShip::draw(){
	glPushMatrix();
	
	glTranslatef(x,y + floatingHeight + floatingY,z);

    glTranslatef(centerX,centerY,centerZ);
    glRotatef(yaw , 0,1,0);
    glRotatef(pitch , 1,0,0);
    glRotatef(roll+addRoll, 0,0,1);
    glScalef(1+addStrecth,1- addStrecth,1);
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

void SpaceShip::setRoll(float _updateRoll){
	if(roll < 0)
		roll += 360;
	else if (roll > 360)
		roll -= 360;

	float updateRollUpLimit = _updateRoll+ 360;
	float updateRollLowLimit = _updateRoll- 360;
	
	float dist1 = fabs(updateRollUpLimit -roll );
	float dist2 = fabs(_updateRoll -roll );
	float dist3 = fabs(updateRollLowLimit - roll);

	if(dist1 <= dist2 && dist1 <= dist3){
		updateRoll = updateRollUpLimit;
	} else if(dist2 <= dist3 && dist2 <= dist1){
		updateRoll = _updateRoll;
	} else {
		updateRoll = updateRollLowLimit;
	}
}

void SpaceShip::setPitch(float _updatePitch){
	if(pitch < 0)
		pitch += 360;
	else if (pitch > 360)
		pitch -= 360;

	float updatePitchUpLimit = _updatePitch+ 360;
	float updatePitchLowLimit = _updatePitch- 360;
	
	float dist1 = fabs(updatePitchUpLimit -pitch );
	float dist2 = fabs(_updatePitch -pitch );
	float dist3 = fabs(updatePitchLowLimit - pitch);

	if(dist1 <= dist2 && dist1 <= dist3){
		updatePitch = updatePitchUpLimit;
	} else if(dist2 <= dist3 && dist2 <= dist1){
		updatePitch = _updatePitch;
	} else {
		updatePitch = updatePitchLowLimit;
	}
}


void SpaceShip::setY(float _y){
	//This function will keep the ship from falling
	//the track will call on it if there is traction
	fallingRate = 0;
	y = _y;

	//Stretching on land
	if(jumped && stretching == 0){
		stretching = 1;
	}
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

float SpaceShip::getFloatingHeight(){
	return floatingHeight;
}

float SpaceShip::getPitch(){
	return pitch;
}

void SpaceShip::jump(){
	if(accelerating  && stretching == 0 && fallingRate == 0 && !jumped){
		stretching = 1;
	}
}

void SpaceShip::startJump(){
	//Setting the falling rate negative for jumping
	fallingRate = -3;
}

bool SpaceShip::isJumping(){
	if(fallingRate <= 0)
		return true;
	return false;
}


