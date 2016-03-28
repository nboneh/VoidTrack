#include "../VoidTrack.h"

//This class performs the count down in the beginning of the game
class Counter{
	float scale, scaleRate;
	bool increasing;
	int currentCount;
	char * text;
	bool started;
	bool playedMusic;
	public: 
		Counter();
		void reset();
		void draw();
		void update(double t);
		bool startShip();
		bool done();

};