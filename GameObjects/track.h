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
		void addNewTrackPieceWidth(float x, float y, float z, float width, float length, float roll, float pitch, float yaw, float xShift);
		void addNewTrackPiece(float x, float y, float z, float length, float roll, float pitch, float yaw);
};