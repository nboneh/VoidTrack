#include "track.h"


Track::Track(){
	setShip = true;

	trackPieces.push_back(new TrackPiece(-3,0,-1
										,6,5
										,0,10,0));

	trackPieces.push_back(new TrackPiece(-3,0.868,-5.924
										,6,5
										,0,20,0));

	trackPieces.push_back(new TrackPiece(-3.000, 2.578 ,-10.622
										,6,20
										,0,30,0));

	trackPieces.push_back(new TrackPiece(-3.000, 17.578 ,-36.603
										,6,5
										,0,25,0));

	trackPieces.push_back(new TrackPiece(-3.000, 19.691 ,-41.135
										,6,5
										,0,15,0));


	trackPieces.push_back(new TrackPiece(-3,19.67,-41.16
										,6,20
										,0,5,0));

	trackPieces.push_back(new TrackPiece(0,19.413,-70.303
										,6,30
										,30,0,20));

	trackPieces.push_back(new TrackPiece(-10.261,19.413,-98.494
										,6,5
										,30,10,30));

	trackPieces.push_back(new TrackPiece(-12.723,20.281,-102.758
										,6,10
										,30,20,30));

	trackPieces.push_back(new TrackPiece(-22.955,26.652,-118.749
										,8,25
										,35,15,45));


	trackPieces.push_back(new TrackPiece(-39.775,32.331,-136.38
										,8,10
										,45,5,70));

	trackPieces.push_back(new TrackPiece(-48.952,32.498,-140.473
									,8,15
									,50,0,80));

	//trackPieces.push_back(new TrackPiece(-58.667,31.855,-142.964
	//								,8,20
	//								,55,-5,90));

	trackPieces.push_back(new TrackPiece(-68.579,30.412,-143.783
								,6,20
								,50,-10,95));

	trackPieces.push_back(new TrackPiece(-97.966,24.57,-141.981
								,6,30
								,40,-5,105));

	//trackPieces.push_back(new TrackPiece(-22.955,26.652,-118.749
	//									,8,25
	//									,50,40,70));

	//trackPieces.push_back(new TrackPiece(-22.341,26.253,-112.891
	//									,6,20
	//									,30,20,40));

	//trackPieces.push_back(new TrackPiece(-28.382,29.674,-120.089
	//									,6,30
	//									,30,20,40));*/


	
	trackPieces.push_back(new TrackPiece(-3,0,7
										,6,8
										,0,0,0));

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
	if(!setShip){
		ship->setX(trackPieces.at(trackPieces.size()-3)->getX());
		ship->setY(trackPieces.at(trackPieces.size()-3)->getY());
		ship->setZ(trackPieces.at(trackPieces.size()-3)->getZ());
		setShip = true;
	}
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
	//Drawing tracks
	for(int i = 0; i<  trackPieces.size(); i++){
		trackPieces.at(i)->draw();
	}
	glUseProgram(0);
	
	glColor3f(liner,lineg, lineb);
	glUseProgram(SIMPLE_LIGHTING_SHADER);
	//Drawing starting line
    glBegin(GL_QUADS);
 	glNormal3f(1,0, 0);
 	glVertex3f(-3,.01,0);
 	glVertex3f(3,.01,0);
 	glVertex3f(3,.01,-1);
 	glVertex3f(-3,.01,-1);
 	glEnd();
 	glUseProgram(0);

}

int Track::getLap(){
	return lap;
}

void Track::setStartLineColor(float r, float g, float b){
	liner = r;
	lineg = g;
	lineb = b;
}

void Track::setShader(int _shader){
	counter = 0;
	shader = _shader; 
}