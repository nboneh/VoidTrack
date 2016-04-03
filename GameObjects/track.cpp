#include "track.h"

float  GEN_WIDTH = 8;


Track::Track(){
	liner = 0;
	lineg =0;
	lineb = 0;
	setShip = true;
	lengthOfTrack = 0;
	 currentXShift= GEN_WIDTH/2 ;
	model = new GLfloat[16];
	glPushMatrix();
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, model);
	glPopMatrix();
	//12,13,14 will represent x, y, and z 
	model[12] = -GEN_WIDTH/2;
	model[13] = 0;
	model[14] = 0 ;
	addNewTrackPiece(0,0,0
										,GEN_WIDTH,10
										,0,0,0 );

	
	//uphill
	for(int i = 0; i <= 30; i+=1){
			addNewTrackPiece(0,0,0
										,GEN_WIDTH,1
										,0,i,0 );							
	}

	addNewTrackPiece(0,0,0
										,GEN_WIDTH,5
										,0,30,0 );	

	addNewTrackPiece(0,0,5
										,GEN_WIDTH,10
										,0,30,0 );	


	addNewTrackPieceTri(0,0,0
										,GEN_WIDTH,10
										,0,30,0 , TOP_RIGHT);	

	addNewTrackPieceTri(4,0,-4
										,GEN_WIDTH,5
										,15,30,0 , BOT_LEFT);

	addNewTrackPiece(0,0,0
										,GEN_WIDTH,15
										,15,30,0 );


	addNewTrackPieceTri(0,0,0
										,GEN_WIDTH,10
										,15,30,0 , TOP_LEFT);

   addNewTrackPieceTri(-5,0,-4
										,GEN_WIDTH,5
										,-15,30,0 , BOT_RIGHT);

	addNewTrackPiece(0,0,0
										,GEN_WIDTH,15
										,-15,30,0 );


	addNewTrackPieceTri(0,0,0
										,GEN_WIDTH,10
										,-15,30,0 , TOP_RIGHT);

	addNewTrackPiece(2,-3,2
										,GEN_WIDTH,10
										,0,30,0 );

		//stop
	for(int i = 30; i >= 0 ; i-=1){
			addNewTrackPiece(0,0,0
										,GEN_WIDTH,1
										,0,i,0 );							
	}

	for(int i = 0; i < 15 ; i+=4){
		int gap = 0;
		if(i% 3 ==0)
			gap = 5;
		addNewYawTurn(0,0,gap
					,GEN_WIDTH,i*2
					,0,0,i, TOP_LEFT,i);						
	}


	for(int i = 0; i >= -30 ; i-=1){
			addNewTrackPiece(0,0,0
										,GEN_WIDTH,1
										,0,i,35);							
	}

	addNewTrackPiece(0,0,4
							,GEN_WIDTH,20
								,3,-30,35);	


	addNewTrackPiece(1,0,4
							,GEN_WIDTH-2,20
								,6,-30,40);		

	addNewTrackPiece(2,0,4
							,GEN_WIDTH-4,20
								,9,-30,45);	


	addNewTrackPiece(-1,0,4
							,GEN_WIDTH-4,20
								,12,-30,50);	

		addNewTrackPiece(-2,0,4
							,GEN_WIDTH-2,20
								,15,-30,55);

	addNewTrackPiece(-2,0,4
						,GEN_WIDTH-1,20
							,10,-25,60);


		addNewTrackPiece(-1,0,4
						,GEN_WIDTH-1,20
							,5,-20,65);

		addNewTrackPiece(-1,0,4
						,GEN_WIDTH,20
							,0,-20,70);

for(int i = -20; i <= 0 ; i++){
			addNewTrackPiece(0,0,0
										,GEN_WIDTH,1
										,0,i,70);							
	}


	addNewTrackPiece(0,0,0
										,GEN_WIDTH,30
										,10,0,90);	




	addNewTrackPiece(0,0,0
										,GEN_WIDTH,30
										,20,0,120);	


	addNewTrackPiece(0,0,0
										,GEN_WIDTH,30
										,30,0,150);	


	addNewTrackPiece(0,0,0
									,GEN_WIDTH,30
									,40,0,180);



	addNewTrackPiece(0,0,0
									,GEN_WIDTH,30
									,30,0,180);

		addNewTrackPiece(0,0,0
									,GEN_WIDTH,30
									,20,0,180);

				addNewTrackPiece(0,0,0
									,GEN_WIDTH,30
									,10,0,180);


		addNewTrackPiece(0,0,4
									,GEN_WIDTH,30
									,10,0,210);
		addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,0,10,210);
		addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,0,20,210);

addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,0,30,210);


		addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,0,40,210);

				addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,0,50,210);

							addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,0,60,210);

					addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,0,50,210);


					addNewTrackPiece(0,0,0
									,GEN_WIDTH-1,10
									,0,40,210);
				addNewTrackPiece(0,0,0
									,GEN_WIDTH-2,10
									,0,30,210);

							addNewTrackPiece(0,0,0
									,GEN_WIDTH-3,10
									,0,20,210);
				addNewTrackPiece(0,0,0
									,GEN_WIDTH-2,10
									,0,10,210);

				addNewTrackPiece(0,0,0
									,GEN_WIDTH-1,10
									,0,0,210);

				addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,0,-10,210);

					addNewTrackPiece(0,0,0
									,GEN_WIDTH-2,10
									,0,-20,210);

						addNewTrackPiece(0,0,0
									,GEN_WIDTH-3,10
									,0,-30,210);
					addNewTrackPiece(0,0,0
									,GEN_WIDTH-2,10
									,0,-20,210);
						addNewTrackPiece(0,0,0
									,GEN_WIDTH-1,10
									,0,-10,225);
						addNewTrackPiece(0,0,0
									,GEN_WIDTH,30
									,0,0,233);

							addNewTrackPiece(0,0,0
									,GEN_WIDTH,30
									,10,0,245);

							addNewTrackPiece(0,0,0
									,GEN_WIDTH,30
									,20,0,257);
						addNewTrackPiece(0,0,0
									,GEN_WIDTH,30
									,30,0,270);

						addNewTrackPiece(0,0,5
									,GEN_WIDTH,25
									,20,0,282);

						addNewTrackPiece(0,0,5
									,GEN_WIDTH,20
									,10,-2,290);
	
								addNewYawTurn(0,0,0
									,GEN_WIDTH,3
									,10,-5,290,TOP_LEFT,20);


	addNewTrackPieceTri(0,0,0
										,GEN_WIDTH,10
										,10,-5,290 , TOP_RIGHT);


						/*	addNewTrackPiece(0,0,0
									,GEN_WIDTH,7
									,5,5,310);

							addNewTrackPiece(0,0,0
									,GEN_WIDTH,7
									,11,10,330);

								addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,17,15,350);


								addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,21,20,10);


								addNewTrackPiece(0,0,0
									,GEN_WIDTH,10
									,25,22,30);*/



	//addNewYawTurn(0,0,0
	//								,GEN_WIDTH,10
	//								,0,0,30, TOP_LEFT,30);


	//	addNewYawTurn(0,0,0
	//								,GEN_WIDTH,10
	//								,0,0,30 , TOP_LEFT);


	free(model);

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
	musicCounter += t;
	sumMusic += ((float)getCurrentLoundnessOfMusic() * t * 50);
	musicSampleCount++;
	loc = glGetUniformLocation(shader, "time");
 	 if (loc>=0) glUniform1f(loc,counter);
 	 if(musicCounter >=.1){
 	 	loc = glGetUniformLocation(shader, "amp");
 	 	if (loc>=0) glUniform1f(loc,sumMusic/(musicSampleCount * 3000) );
 	 	musicCounter = 0 ;
 	 	sumMusic = 0;
 	 	musicSampleCount = 0;
 	}
  	glUseProgram(0);
}

bool Track::checkTraction(SpaceShip* ship){
	if(!setShip){
		ship->setX(trackPieces.at(trackPieces.size()-1)->getX());
		ship->setY(trackPieces.at(trackPieces.size()-1)->getY());
		ship->setZ(trackPieces.at(trackPieces.size()-1)->getZ());
		setShip = true;
	}
	for(int i = 0; i < trackPieces.size(); i++){
		if(trackPieces.at(i)->checkTraction(ship)){

			if(lap >= 1 && zoneCount1 && i > trackPieces.size()*.5){
				lap++;
				zoneCount1 = false;
			}
			if(lap >= 1 && zoneCount2 && i > trackPieces.size()*.82){
				lap++;
				zoneCount2 = false;
			}

			if(i < currentTrackPiece){
				//Lap complete
				lap++;
				zoneCount2 = true;
				zoneCount1 = true;

			}
			currentTrackPiece = i;
			return true;
		}
	}
	return false;
}

void Track::reset(){
	counter = 0;
	currentTrackPiece = 0;
	lap = 0;
	zoneCount2 = true;
	zoneCount1 = true;
	musicCounter = 0;
	sumMusic = 0;
	musicSampleCount = 0;
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
 	glVertex3f(-4,.01,0);
 	glVertex3f(4,.01,0);
 	glVertex3f(4,.01,-1);
 	glVertex3f(-4,.01,-1);
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

void Track::addNewTrackPiece(float moveRight, float moveUp, float moveFor, float width,float length, float roll, float pitch, float yaw){
		addNewTrackPieceTri(moveRight,moveUp,moveFor, width, length, roll, pitch,yaw, -1);
}

void Track::addNewTrackPieceTri(float moveRight, float moveUp, float moveFor, float width, float length, float roll, float pitch, float yaw, int deactiveCorner){
		moveFor = -moveFor;
		float x = model[12] + model[0] * moveRight + model[4] * moveUp +model[8] * moveFor; 
		float y = model[13]+ model[1] * moveRight + model[5] * moveUp +model[9] * moveFor; 
		float z = model[14]+ model[2] * moveRight + model[6] * moveUp + model[10] * moveFor; 
		TrackPiece *trackpiece = new TrackPiece(x,y,z
										,width,length
										,roll,pitch,yaw, lengthOfTrack,currentXShift,model);
		if(deactiveCorner >= 0)
			trackpiece->makeIntoTriangle(deactiveCorner);

		trackPieces.push_back(trackpiece);
		lengthOfTrack += length;
}

void Track::addNewYawTurn(float moveRight, float moveUp, float moveFor, float width, float length, float roll, float pitch, float currentYaw, int deactiveCorner, float yaw){
		moveFor = -moveFor;
	float x = model[12] + model[0] * moveRight + model[4] * moveUp +model[8] * moveFor; 
	float y = model[13]+model[1] * moveRight + model[5] * moveUp +model[9] * moveFor; 
	float z = model[14]+ model[2] * moveRight + model[6] * moveUp + model[10] * moveFor; 


	//Finding side lenght of triangle
	float sideLength = fabs(width*Tan(yaw));
	//Adding triangle
	TrackPiece *tripiece = new TrackPiece(x,y,z
										,width,sideLength
										,roll,pitch,currentYaw, lengthOfTrack,currentXShift,model);
	tripiece->makeIntoTriangle(deactiveCorner);


	float sqx = model[12];
	float sqy = model[13];
	float sqz = model[14];
	//Adjusting x  y and z accordingly to be able to connect pieces
	if(deactiveCorner == TOP_LEFT){
		sqx =x;
		sqy =y;
		sqz =z;
	}

	//Finding length added to the track by triangle using law of cosines
	float hyp = sqrt(sideLength*sideLength + width*width);

	float hypcenter = hyp/2;
	float widthcenter = width/2;

	float triaddLength = sqrt(hypcenter*hypcenter + widthcenter*widthcenter - 2 *hypcenter*widthcenter*Cos(yaw));
	lengthOfTrack += triaddLength;
//	Log("%f",triaddLength);
	tripiece->setShiftAngle(yaw);
	trackPieces.push_back(tripiece);


	//Adding square also have to change gen width to get a new center point
	float lengthOfSquare = length;
	float widthOfSquare = hyp;

	currentXShift +=(widthOfSquare - GEN_WIDTH)/2.0;
	GEN_WIDTH = widthOfSquare;


	TrackPiece *trackpiece = new TrackPiece(sqx,sqy,sqz
										,widthOfSquare,lengthOfSquare
										,roll,pitch,currentYaw+ yaw, lengthOfTrack,currentXShift,model);

	lengthOfTrack += lengthOfSquare;



	trackPieces.push_back(trackpiece);

}

