#include "../VoidTrack.h"

class Flame{
	int numOfParticles;
	float * Vert;
	float * DurationTime;
	float * Color;
	float * Vel;

	float counter;
	float lastVelocity;

	float lowR, highR, lowG, highG, lowB, highB;
	public:
		Flame();
		void reset();
	    void update(float t, float velocity);
	    void draw();
	    void setColor(float r1,float g1,float b1, float r2, float g2, float b2);

};