#include "../VoidTrack.h"

#ifndef SPACESHIP_H
#include "spaceship.h"
#endif

class TrackPiece{
	//A cube plank that can be set up in 3d space
	float x, y, z, width,length,height, roll, pitch, yaw;

	//These shifts for the shader to allign it
	float shiftX, shiftZ;

	float diff3;
	//For changing y based on roll and pitch of the track piece
	float pitchSlope;
	float rollSlope;

	//Our hit detection will work based on a projected rectangle on the z and x axis plane
	float hitX1, hitZ1, hitX2, hitZ2, hitX3, hitZ3, hitX4, hitZ4;
	float hitRectArea;


	public: 
		TrackPiece(float x, float y, float z, float width, float length, float roll, float pitch, float yaw);
		void setColor(float r, float g, float b);
		void draw();
		bool checkTraction(SpaceShip* ship);

		float getX();
		float getY();
		float getZ();

};