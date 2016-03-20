#include "../VoidTrack.h"
#include "flame.h"

#ifndef SPACESHIP_H
#define SPACESHIP_H
#endif

class SpaceShip{

	float terminalVelocity, accelerationRate,velocity, floatingMotionCounter;
	bool accelerating, falling;
	float x,y,z,roll, pitch, yaw, floatingHeight;
	float centerX, centerY, centerZ;
	Flame * flame;

	//For turning
	int rollRate, maxAddRoll;
	float addRoll;

	float addY;

	//1 for right, 0 for no, -1 for left
	int turn;

	//For falling
	int pitchRate, maxAddPitch;
	float addPitch, fallingRate;

	public: 
		SpaceShip();
		void reset();
		void update(double t);
		void draw();

		void increaseTerminalVelocityBy(float add);

		void setRoll(float _roll);
		void setPitch(float _pitch);

		void turnLeft();
		void stopTurnLeft();

		void turnRight();
		void stopTurnRight();

		void turnDrifitingOn();
		void turnDrifitingOff();


		void go();

		float getX();
		float getY();
		float getZ();
		
		float getYaw();
		float getPitch();

		void setFalling();

	private:
		void floatingMotion(double t);
};