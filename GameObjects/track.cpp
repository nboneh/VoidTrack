#include "track.h"


Track::Track(){
	
	trackPieces.push_back(new TrackPiece(-.5,-1,-14
										,3,3,5
										,40,0,0));

	trackPieces.push_back(new TrackPiece(-.5,3,-9
										,2,3,5
										,0,-40,0));
	
	trackPieces.push_back(new TrackPiece(-.5,-.06,-5
										,2,2,5
										,0,40,0));
	
	trackPieces.push_back(new TrackPiece(-1.5,0,0
										,4,3,5
										,0,0,0));
	reset();
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