#include "../VoidTrack.h"
#include "flame.h"

#ifndef SPACESHIP_H
#define SPACESHIP_H
#endif

class SpaceShip{

	float terminalVelocity, accelerationRate,velocity, floatingMotionCounter;
	bool accelerating,  updateFallingOn, jumpOn;
	float x,y,z,roll, pitch, yaw, floatingHeight, updateRate;
	float centerX, centerY, centerZ;
	Flame * flame;

	float updatePitch, updateRoll;

	float jumpVel;

	//For turning
	int rollRate, maxAddRoll;
	float addRoll;

	float floatingY;


	GLfloat *model; 

	//1 for right, 0 for no, -1 for left
	int turn;

	float fallingRate;
	float fallingRateInc;
	// stretching int 1 for increase stretch and -1 for decrease
	int stretching;
	float addStrecth, maxStrecth, stretchRate;

	float pr, pb, pg, cr, cb , cg; 

	public: 
		SpaceShip();
		void reset();
		void update(double t);
		void draw();

		void stop();

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

		void jump();
		bool isJumping();

		float getX();
		float getY();
		float getFloatingHeight();
		float getZ();

		float* getUpVector();
		float* getForwardVector();

		void setColor(float pr, float pb,  float pg, float cr, float cb, float cg  );

		void setLandingY(float y);

		void setStretchingForVel(float vel);
		
		float getYaw();
		float getPitch();
		float getRoll();

		bool fallen();


		void setX(float _x);
		void setY(float _y);
		void setZ(float _z);



	private:
		void updateModelMatrix();
		void floatingMotion(double t);
		void updateTurning(double t);
		void updateFalling(double t);
		void updateValues(double t);
		void updateStretch(double t);
		void startJump();
};