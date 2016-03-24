#include "track.h"


Track::Track(){
	trackPieces.push_back(new TrackPiece(-2,0,7
										,5,8
										,0,0,0));


	trackPieces.push_back(new TrackPiece(-2,-1,0
										,4,50
										,20,-20,20));


	//trackPieces.push_back(new TrackPiece(2,0,-4
	//									,4,20
	//   								,0,20,-40));

	//trackPieces.push_back(new TrackPiece(0,0,-4
	//									,40,20
	//   								,0,40,0));
	//trackPieces.push_back(new TrackPiece(0,0,-4
	//									,40,20
	 //  								,0,40,0));
	//trackPieces.push_back(new TrackPiece(0,0,-4
	//									,80,80,
	//   								40,40,30));
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

void Track::setColor(float r1, float g1, float b1, float r2, float g2, float b2){
	 glUseProgram(shader);
	 int loc;
	 loc = glGetUniformLocation(shader, "PrimeColor");
 	 if (loc>=0) glUniform3f(loc,r1,g1,b1);
 	 loc = glGetUniformLocation(shader, "ComplimentColor");
 	 if (loc>=0) glUniform3f(loc,r2,g2,b2);
}
void Track::update(float t){
	counter += t;
	 glUseProgram(shader);
	int loc;
	counter += t;
	loc = glGetUniformLocation(shader, "time");
 	 if (loc>=0) glUniform1f(loc,counter);
  	glUseProgram(0);
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
	counter = 0;
	currentTrackPiece = trackPieces.size()-1;
	lap = 0;
}

void Track::draw(){
	glUseProgram(shader);
	for(int i = 0; i < trackPieces.size(); i++){
		trackPieces.at(i)->draw();
	}
	glUseProgram(0);
}

int Track::getLap(){
	return lap;
}

void Track::setShader(int _shader){
	counter = 0;
	shader = _shader; 
}