#include "track.h"

float  GEN_WIDTH = 8;


Track::Track(){
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
	addNewTrackPiece(0,0,1
										,GEN_WIDTH,10
										,0,0,0 );

	
	//uphill
	/*for(int i = 0; i <= 30; i+=1){
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
										,GEN_WIDTH,10
										,15,30,0 );


	addNewTrackPieceTri(0,0,0
										,GEN_WIDTH,10
										,15,30,0 , TOP_LEFT);

   addNewTrackPieceTri(-5,0,-4
										,GEN_WIDTH,5
										,-15,30,0 , BOT_RIGHT);

	addNewTrackPiece(0,0,0
										,GEN_WIDTH,10
										,-15,30,0 );


	addNewTrackPieceTri(0,0,0
										,GEN_WIDTH,10
										,-15,30,0 , TOP_RIGHT);

	addNewTrackPiece(2,-3,2
										,GEN_WIDTH,10
										,0,30,0 );*/


	addNewYawTurn(0,0,0
									,GEN_WIDTH,10
									,0,0,0 , TOP_RIGHT,30);

	addNewYawTurn(0,0,0
									,GEN_WIDTH,10
									,0,0,-30 , TOP_RIGHT,30);


	//	addNewYawTurn(0,0,0
	//								,GEN_WIDTH,10
	//								,0,0,30 , TOP_LEFT);



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
		ship->setX(trackPieces.at(trackPieces.size()-50)->getX());
		ship->setY(trackPieces.at(trackPieces.size()-50)->getY());
		ship->setZ(trackPieces.at(trackPieces.size()-50)->getZ());
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

void Track::addNewTrackPiece(float moveRight, float moveUp, float moveFor, float width,float length, float roll, float pitch, float yaw){
		addNewTrackPieceTri(moveRight,moveUp,moveFor, width, length, roll, pitch,yaw, -1);
}

void Track::addNewTrackPieceTri(float moveRight, float moveUp, float moveFor, float width, float length, float roll, float pitch, float yaw, int deactiveCorner){
		 currentXShift -= moveRight;
		float x = model[12] + model[0] * moveRight + model[1] * moveUp +model[2] * moveFor; 
		float y = model[13]+ model[4] * moveRight + model[5] * moveUp +model[6] * moveFor; 
		float z = model[14]+ model[8] * moveRight + model[9] * moveUp - model[10] * moveFor; 
		TrackPiece *trackpiece = new TrackPiece(x,y,z
										,width,length
										,roll,pitch,yaw, lengthOfTrack,currentXShift,model);
		if(deactiveCorner >= 0)
			trackpiece->makeIntoTriangle(deactiveCorner);

		trackPieces.push_back(trackpiece);
		lengthOfTrack += length;
}

void Track::addNewYawTurn(float moveRight, float moveUp, float moveFor, float width, float length, float roll, float pitch, float currentYaw, int deactiveCorner, float yaw){
	currentXShift -= moveRight;
	float x = model[12] + model[0] * moveRight + model[1] * moveUp +model[2] * moveFor; 
	float y = model[13]+ model[4] * moveRight + model[5] * moveUp +model[6] * moveFor; 
	float z = model[14]+ model[8] * moveRight + model[9] * moveUp - model[10] * moveFor; 


	//Finding side lenght of triangle
	float sideLength = fabs(width*Tan(yaw));
	//Adding triangle
	TrackPiece *tripiece = new TrackPiece(x,y,z
										,width,sideLength
										,roll,pitch,currentYaw, lengthOfTrack,currentXShift,model);
	tripiece->makeIntoTriangle(deactiveCorner);
		if(TOP_RIGHT)
			yaw = -yaw;
	//Adjusting x  y and z accordingly to be able to connect pieces
	float sqx = model[12];
	float sqy = model[13];
	float sqz = model[14];
	//sqx = x;
	//sqy= y;
	//if(deactiveCorner == TOP_LEFT){
	//	sqz =z;
	//}

	//Finding length added to the track by triangle using law of cosines
	float hyp = sqrt(sideLength*sideLength + width*width);

	float hypcenter = hyp/2;
	float widthcenter = width/2;

	float triaddLength = sqrt(hypcenter*hypcenter + widthcenter*widthcenter - 2 *hypcenter*widthcenter*Cos(yaw));
	lengthOfTrack += triaddLength;
//	Log("%f",triaddLength);
	tripiece->setLenRelToTrack(triaddLength);
	tripiece->setShiftAngle(yaw);
	trackPieces.push_back(tripiece);


	//Adding square also have to change gen width to get a new center point
	float lengthOfSquare = length -triaddLength;
	float widthOfSquare = hyp;

	currentXShift +=(widthOfSquare - GEN_WIDTH)/2.0;
	GEN_WIDTH = widthOfSquare;


	TrackPiece *trackpiece = new TrackPiece(sqx,sqy,sqz
										,widthOfSquare,lengthOfSquare
										,roll,pitch,currentYaw+ yaw, lengthOfTrack,currentXShift,model);

	lengthOfTrack += lengthOfSquare;



	trackPieces.push_back(trackpiece);

}

