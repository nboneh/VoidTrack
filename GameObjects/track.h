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
	float liner, lineg, lineb;


	bool setShip;

	float lengthOfTrack;

	GLfloat * model;
		float currentXShift;

	public: 
		Track();
		void reset();
		void draw();
		void update(float t);
		
		bool checkTraction(SpaceShip* ship);

		int getLap();

		void setColor(float pr, float pg, float pb, float cr, float cg, float cb);
		void setStartLineColor(float r, float g, float b);
		void setShader(int shader);
	private:
		void addNewTrackPiece(float moveRight, float moveUp, float moveFor, float width,float length, float roll, float pitch, float yaw);
		void addNewTrackPieceTri(float moveRight, float moveUp, float moveFor, float width, float length, float roll, float pitch, float yaw, int deactiveCorner);
		void addNewYawTurn(float moveRight, float moveUp, float moveFor, float width, float length, float roll, float pitch, float currentYaw, int deactiveCorner, float yaw);
		
		void getXYZfromVectors(float moveRight, float moveUp, float moveFor);
};