#include "track.h"


Track::Track(){
	
	trackPieces.push_back(new TrackPiece(-1,0,0
										,2,3
										,0,0,0));


	trackPieces.push_back(new TrackPiece(-.5,-.06,-2
										,4,20
										,40,0,0));

	trackPieces.push_back(new TrackPiece(-.5,0,-20
										,4,20
										,0,20,0));

	//trackPieces.push_back(new TrackPiece(-.5,0,-20
										//,20,5
										//,0,0,0));
	

	reset();
}	

bool Track::checkTraction(SpaceShip* ship){

	for(int i = 0; i < trackPieces.size(); i++){
		if(trackPieces.at(i)->checkTraction(ship)){
			currentTrackPiece = i;
			return true;
		}
	}
	return false;
}

void Track::reset(){
	currentTrackPiece = 0;
}

void Track::draw(){
	glColor3f(0,0,1);
	for(int i = 0; i < trackPieces.size(); i++){
		trackPieces.at(i)->draw();
	}
}