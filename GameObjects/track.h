#include "../VoidTrack.h"
#include "trackpiece.h"
#include <vector>

#ifndef SPACESHIP_H
#include "spaceship.h"
#endif



class Track{
	std::vector<TrackPiece *> trackPieces;
	int currentTrackPiece;
	int lap;
	int shader;
	float counter;

	public: 
		Track();
		void reset();
		void draw();
		void update(float t);
		
		bool checkTraction(SpaceShip* ship);

		int getLap();

		void setColor(float pr, float pg, float pb, float cr, float cg, float cb);
		void setShader(int shader);

};