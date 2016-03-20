#include "../VoidTrack.h"

#ifndef SPACESHIP_H
#include "spaceship.h"
#endif

class TrackPiece{
	float x, y, z, width, endWidth, length, roll, pitch, yaw;
	float widthDiff;
	float trackHeight;
	public: 
		TrackPiece(float x, float y, float z, float width, 
			float endWidth, float length, float roll, float pitch, float yaw);
		void setColor(float r, float g, float b);
		void draw();
		bool checkTraction(SpaceShip ship);

};