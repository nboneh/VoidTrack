#include "../VoidTrack.h"
#include "trackpiece.h"
#include <vector>

#ifndef SPACESHIP_H
#include "spaceship.h"
#endif



class Track{
	std::vector<TrackPiece *> trackPieces;
	int currentTrackPiece;

	public: 
		Track();
		void reset();
		void draw();
		
		bool checkTraction(SpaceShip* ship);

};