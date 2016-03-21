#include "../VoidTrack.h"
#include "flame.h"

#ifndef SPACESHIP_H
#define SPACESHIP_H
#endif

class SpaceShip{

	float terminalVelocity, accelerationRate,velocity, floatingMotionCounter;
	bool accelerating, jumped;
	float x,y,z,roll, pitch, yaw, floatingHeight, updateRate;
	float centerX, centerY, centerZ;
	Flame * flame;

	float updatePitch, updateRoll;

	//For turning
	int rollRate, maxAddRoll;
	float addRoll;

	float floatingY;

	//1 for right, 0 for no, -1 for left
	int turn;

	float fallingRate;

	//For before the jump, stretching int 1 for increase stretch and -1 for decrease
	int stretching;
	float addStrecth, maxStrecth, stretchRate;

	public: 
		SpaceShip();
		void reset();
		void update(double t);
		void draw();

		void increaseTerminalVelocityBy(float add);
		void stopMoving();

		void setRoll(float _roll);
		void setPitch(float _pitch);

		void turnLeft();
		void stopTurnLeft();

		void turnRight();
		void stopTurnRight();

		void turnDrifitingOn();
		void turnDrifitingOff();


		void go();

		void jump();
		bool isJumping();

		float getX();
		float getY();
		float getFloatingHeight();
		float getZ();

		void setY(float y);
		
		float getYaw();
		float getPitch();


	private:
		void floatingMotion(double t);
		void updateTurning(double t);
		void updateFalling(double t);
		void updateValues(double t);
		void updateStretch(double t);
		void startJump();
};