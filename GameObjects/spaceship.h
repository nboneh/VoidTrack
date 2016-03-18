#include "../VoidTrack.h"

class SpaceShip{

	float terminalVelocity;
	float accelerationRate;
	bool accelerating;
	float velocity;
	float x,y,z,roll, pitch, yaw, floatingMotionCounter;

	public: 
		SpaceShip();
		void reset();
		void update(double t);
		void draw();

		void increaseTerminalVelocityBy(float add);

		void setRoll(float _roll);
		void setPitch(float _pitch);

		void go();

		float getX();
		float getY();
		float getZ();
		
		float getYaw();
		float getPitch();

	private:
		void floatingMotion(double t);
};