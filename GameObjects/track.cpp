#include "track.h"


Track::Track(){
	trackPieces.push_back(new TrackPiece(-2,0,7
										,5,8
										,0,0,0));


	//trackPieces.push_back(new TrackPiece(-2,0,-4
	//									,4,50
	//									,-20,0,40));


	//trackPieces.push_back(new TrackPiece(2,0,-4
	//									,4,20
	//   								,0,20,-40));

	//trackPieces.push_back(new TrackPiece(0,0,-4
	//									,40,20
	//   								,0,40,0));
	//trackPieces.push_back(new TrackPiece(0,0,-4
	//									,40,20
	 //  								,0,40,0));
	trackPieces.push_back(new TrackPiece(0,0,-4
										,80,80,
	   								40,40,0));
	//	trackPieces.push_back(new TrackPiece(0,0,-4
	//									,10,10
	 //  								,0,0,0));

	//trackPieces.push_back(new TrackPiece(-.5,0,-20
										//,20,5
										//,0,0,0));


	//trackPieces.push_back(new TrackPiece(-5,-1,20
	//									,40,20
	//									,0,40,40));
	

	reset();
}	

bool Track::checkTraction(SpaceShip* ship){

	for(int i = 0; i < trackPieces.size(); i++){
		if(trackPieces.at(i)->checkTraction(ship)){
			if(i < currentTrackPiece){
				//Lap complete
				lap++;
			}

			currentTrackPiece = i;
			return true;
		}
	}
	return false;
}

void Track::reset(){
	currentTrackPiece = trackPieces.size()-1;
	lap = 0;
}

void Track::draw(){
	glColor3f(0,0,1);
	for(int i = 0; i < trackPieces.size(); i++){
		trackPieces.at(i)->draw();
	}
}

int Track::getLap(){
	return lap;
}