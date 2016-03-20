#include "track.h"


Track::Track(){
	trackPieces.push_back(new TrackPiece(-.5,0,0,3,2,4,0,0,0));
	reset();
}	

void Track::reset(){
	currentTrackPiece = 0;
}

void Track::draw(){
	glColor3f(1,1,1);
	for(int i = 0; i < trackPieces.size(); i++){
		trackPieces.at(i)->draw();
	}
}