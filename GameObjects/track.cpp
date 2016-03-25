#include "track.h"

const float  GEN_WIDTH = 7;


Track::Track(){
	setShip = true;
	lengthOfTrack = 0;


	addNewTrackPiece(-3.5,0,-1
										,5
										,0,5,0 );
	addNewTrackPiece(-3.500, 0.436 ,-5.981
										,5
										,0,10,0 );
	addNewTrackPiece(-3.500, 1.304 ,-10.905
										,5
										,0,15,0 );
	addNewTrackPiece(-3.500, 2.598 ,-15.735
										,5
										,0,20,0 );

	addNewTrackPiece(-3.500, 4.308 ,-20.433
										,5
										,0,25,0 );

	addNewTrackPiece(-3.500, 6.421 ,-24.965
										,5
										,0,30,0 );


	addNewTrackPieceWidth(-3.500, 8.921 ,-29.295,
										GEN_WIDTH-1,5
										,0,30,0,GEN_WIDTH/2);

	addNewTrackPieceWidth(-3.500, 11.421 ,-33.625,
										GEN_WIDTH-2,5
										,0,30,0,GEN_WIDTH/2);


	addNewTrackPieceWidth(-3.500, 13.921 ,-37.955,
										GEN_WIDTH-3,5
										,0,30,0,GEN_WIDTH/2);


	addNewTrackPieceWidth(-3.500, 16.421 ,-42.285,
										GEN_WIDTH-4,5
										,0,30,0,GEN_WIDTH/2);

	addNewTrackPieceWidth(-3.500, 18.921 ,-46.615,
									GEN_WIDTH-5,5
									,0,30,0,GEN_WIDTH/2);

	addNewTrackPieceWidth(-3.500, 21.421 ,-50.945,
									GEN_WIDTH-5,5
									,0,30,0,GEN_WIDTH/2);


	addNewTrackPieceWidth(2.500, 23.921 ,-55.275,
										GEN_WIDTH-5,5
										,0,30,0,GEN_WIDTH/2-5);


	addNewTrackPieceWidth(1.500, 26.421 ,-59.605,
										GEN_WIDTH-4,5
										,0,30,0,GEN_WIDTH/2-4);

	addNewTrackPieceWidth(0.500, 28.921 ,-63.935,
										GEN_WIDTH-3,5
										,0,30,0,GEN_WIDTH/2-3);


	addNewTrackPieceWidth(-0.500, 31.421 ,-68.265,
										GEN_WIDTH-2,5
										,0,30,0,GEN_WIDTH/2-2);


	addNewTrackPieceWidth(-1.500, 33.921 ,-72.595,
										GEN_WIDTH-1,5
										,0,30,0,GEN_WIDTH/2-1);


	addNewTrackPiece(-2.500, 36.421 ,-76.925,
										5
										,0,30,0);


	addNewTrackPiece(-2.500, 38.921 ,-81.255,
										10
										,0,35,0);

	addNewTrackPieceWidth(-2.500, 44.657 ,-89.447,
										3.5,10
										,0,35,0,GEN_WIDTH/2);

	addNewTrackPiece(-2.500, 50.393 ,-97.639,
									10
									,0,35,0);


	addNewTrackPieceWidth(1.000, 56.129 ,-105.831,
									3.5,10
									,0,35,0, GEN_WIDTH/2-3.5);

	addNewTrackPiece(-2.500, 61.865 ,-114.023,
									10
									,0,35,0);

	addNewTrackPieceWidth(-2.500, 67.601 ,-122.215,
								1.75,10
								,0,35,0, GEN_WIDTH/2);

	addNewTrackPieceWidth(2.750, 67.601 ,-122.215,
								1.75,10
								,0,35,0, GEN_WIDTH/2-5.75);

	addNewTrackPiece(-2.500, 73.337 ,-130.407,
								10
								,0,35,0);
	addNewTrackPiece(-2.500, 79.073 ,-138.599,
								5
								,0,30,0);

	addNewTrackPiece(-2.500, 81.573 ,-142.929,
								5
								,0,25,0);

	addNewTrackPiece(-2.500, 83.686 ,-147.461,
								5
								,0,20,0);


	addNewTrackPiece(-2.500, 85.396 ,-152.159,
								5
								,0,15,0);

	addNewTrackPiece(-2.500, 86.690 ,-156.989,
								5
								,0,10,0);

	addNewTrackPiece(-2.500, 87.558 ,-161.913,
							5
							,0,5,0);


	addNewTrackPiece(-2.500, 87.994 ,-166.894,
							5.6
							,0,0,0);

	addNewTrackPiece(-2.500, 87.995 ,-171.894,
							5.6
							,0,0,5);

	addNewTrackPiece(-2.936, 87.996 ,-176.875,
							5.6
							,0,0,10);


	addNewTrackPiece(-3.804, 87.997 ,-181.799,
							5.6
							,0,0,15);

	addNewTrackPiece(-5.098, 87.998 ,-186.629,
							5.6
							,0,0,20);


	addNewTrackPiece(-6.808, 87.999 ,-191.327,
							5.6
							,0,0,25);



	addNewTrackPiece(-11.034, 88.01 ,-200.391,
						5.6
						,0,0,30);

	addNewTrackPiece(-13.534, 88.015 ,-204.721,
						5.6
						,0,0,35);


	addNewTrackPiece(-16.402, 88.020 ,-208.817,
						5.6
						,0,0,40);

	
	addNewTrackPiece(-19.616, 88.030 ,-212.647,
						5.6
						,0,0,45);

	addNewTrackPiece(-23.152, 88.040 ,-216.183,
						5.6
						,0,0,50);

	addNewTrackPiece(-26.982, 88.050 ,-219.397,
						5.6
						,0,0,55);

	addNewTrackPiece(-35.408, 88.050 ,-224.765,
						5
						,0,0,65);

	addNewTrackPiece(-39.940, 88.050 ,-226.878,
						5
						,0,-5,65);

	addNewTrackPiece(-44.454, 87.614 ,-228.983,
						5
						,0,-10,65);

	addNewTrackPiece(-48.917, 86.746 ,-231.064,
						5
						,0,-15,65);

	addNewTrackPiece(-53.294, 85.452 ,-233.105,
						5
						,0,-20,65);

	addNewTrackPiece(-57.552, 83.742 ,-235.091,
						5
						,0,-25,65);

	addNewTrackPiece(-61.659, 81.629 ,-237.006,
						5
						,0,-30,65);

	addNewTrackPiece(-65.583, 79.129 ,-238.836,
						5
						,2.5,-30,61.33);

	addNewTrackPiece(-69.382, 76.629 ,-240.913,
						5
						,5.36,-35,58.46);

	addNewTrackPiece(-72.873, 73.761 ,-243.055,
						5
						,8.57,-40,54.62);

	addNewTrackPiece(-75.996, 70.547 ,-245.273,
						5.6
						,8.57,-40,54.62);

	addNewTrackPiece(-79.119, 67.333 ,-247.491,
						5.6
						,5.35,-40,58.45);

	addNewTrackPiece(-82.383, 64.119 ,-249.495,
						5.6
						,2.136,-40,62.28);

	//addNewTrackPiece(-82.383, 64.119 ,-249.495,
	//					3.2
	//					,0,-40,64.87);


	addNewTrackPieceWidth(-90.220, 56.856 ,-253.171,
						5, 15
						,0,-40,64.87,GEN_WIDTH/2);

	addNewTrackPieceWidth(-105.322, 42.072 ,-262.464,
						5, 15
						,0,-40,64.87,GEN_WIDTH/2-2);


	addNewTrackPieceWidth(-122.123, 27.288 ,-268.136,
						3, 15
						,0,-40,64.87,GEN_WIDTH/2);

	addNewTrackPieceWidth(-133.601, 15.075 ,-277.938,
						4, 15
						,0,-40,64.87,GEN_WIDTH/2-4);

	

	addNewTrackPiece(-148.477, 2.862 ,-280.498,
						 15
						,0,-40,64.87);


	addNewTrackPiece(-158.880, -6.780 ,-285.378,
						 12
						,0,-30,64.87);


	addNewTrackPiece(-166.721, -11.780 ,-289.056,
						 10
						,-3.42,-20,74.2669);











	


	addNewTrackPiece(-3.5,0,7
										,8
										,0,0,0);



	reset();
}	

void Track::setColor(float r1, float g1, float b1, float r2, float g2, float b2){
	 glUseProgram(shader);
	 int loc;
	 loc = glGetUniformLocation(shader, "PrimeColor");
 	 if (loc>=0) glUniform3f(loc,r1,g1,b1);
 	 loc = glGetUniformLocation(shader, "ComplimentColor");
 	 if (loc>=0) glUniform3f(loc,r2,g2,b2);
 	 glUseProgram(0);
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
		ship->setX(trackPieces.at(trackPieces.size()-15)->getX());
		ship->setY(trackPieces.at(trackPieces.size()-15)->getY());
		ship->setZ(trackPieces.at(trackPieces.size()-15)->getZ());
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
 	glVertex3f(-3.5,.01,0);
 	glVertex3f(3.5,.01,0);
 	glVertex3f(3.5,.01,-1);
 	glVertex3f(-3.5,.01,-1);
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

void Track::addNewTrackPieceWidth(float x, float y, float z, float width, float length, float roll, float pitch, float yaw, float xShift){
		trackPieces.push_back(new TrackPiece(x,y,z
										,width,length
										,roll,pitch,yaw, lengthOfTrack,xShift));

	lengthOfTrack += length;
}


void Track::addNewTrackPiece(float x, float y, float z, float length, float roll, float pitch, float yaw){
		addNewTrackPieceWidth(x,y,z, GEN_WIDTH, length, roll, pitch,yaw, GEN_WIDTH/2);
}