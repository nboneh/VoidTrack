#include "../VoidTrack.h"


class Flame{
	int numOfParticles;
	int shader;
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
	private:
		void init();

};