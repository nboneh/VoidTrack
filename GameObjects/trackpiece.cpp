#include "trackpiece.h"

TrackPiece::TrackPiece(float _x, float _y, float _z, float _width, 
				 float _length, float _roll, float _pitch, float _yaw,float lengthFromStart, float _shiftX, GLfloat *model){

	height = .2;
	deactiveCorner = -1;
	x = _x;
	y = _y;
	z = _z;
	width = _width;
	//Extend length slightly to connect tracks better use the given length for calc
	length = _length;
	roll = _roll;
	pitch = _pitch;
	yaw = _yaw;
	shiftX = _shiftX;


	glPushMatrix();
	glLoadIdentity();
    glRotatef(yaw , 0,1,0);
    glRotatef(pitch , 1,0,0);
    glRotatef(roll, 0,0,1);
	glGetFloatv(GL_MODELVIEW_MATRIX, model);
	glPopMatrix();


	hitX1 = x;
	hitZ1 = z;

	float zcalc1 = length *model[10];
	float zcalc2 = width * model[2];

	float xcalc1 = width *model[0];
	float xcalc2 = length *model[8];

	hitX2 = x + xcalc1;
	hitZ2 = z +zcalc2;

	hitX3 = x -xcalc2 +xcalc1; 
	hitZ3 = z  - zcalc1 +zcalc2;

	hitX4 = x  -xcalc2;
	hitZ4 = z - zcalc1;


	//The length of the projection in the z does not equal the length
	float xdiff3 = hitX4 -x;
	float zdiff3 = hitZ4 -z;
	diff3 = sqrt(xdiff3 * xdiff3 + zdiff3*zdiff3);

	shiftZ  = lengthFromStart;

	hitRectArea = areaOfTrianlge(hitX1, hitZ1, hitX2, hitZ2, hitX3, hitZ3);
	hitRectArea += areaOfTrianlge(hitX2, hitZ2, hitX3, hitZ3, hitX4, hitZ4);

	GLfloat *slopeModel = new GLfloat[16];
	glPushMatrix();
	glLoadIdentity();
    glRotatef(pitch , 1,0,0);
    glRotatef(roll, 0,0,1);
	glGetFloatv(GL_MODELVIEW_MATRIX, slopeModel);
	glPopMatrix();

		
	//Raise over run using the model matrix to calculate slopes
	rollSlope =  -(slopeModel[4])/(slopeModel[5]);
	pitchSlope = (slopeModel[6])/(slopeModel[5]);
	free(slopeModel);

    //Setting model x, y and, z to end of the piece to help with track building
	model[12] =hitX4;
	model[13] =  y - length *model[9];
	model[14] = hitZ4;
	shiftAngle = 0;
}	

void TrackPiece::makeIntoTriangle(int _deactiveCorner){
	deactiveCorner = _deactiveCorner;
	switch(deactiveCorner){
		case BOT_LEFT:
			hitRectArea = areaOfTrianlge(hitX2, hitZ2, hitX3, hitZ3, hitX4, hitZ4);
		   	  break;
	    case BOT_RIGHT:
	    	hitRectArea = areaOfTrianlge(hitX1, hitZ1, hitX3, hitZ3, hitX4, hitZ4);
	    	break;
	    case TOP_RIGHT:
	    	hitRectArea = areaOfTrianlge(hitX1, hitZ1, hitX2, hitZ2, hitX4, hitZ4);
	    	break;
		 case TOP_LEFT:
	      	hitRectArea = areaOfTrianlge(hitX1, hitZ1, hitX2, hitZ2, hitX3, hitZ3);
	    	break;
	    default:
	    	break;
	}
}
void TrackPiece::draw(){	

    glVertexAttrib2f(SHIFTS, shiftX, shiftZ);

	glPushMatrix();
	glTranslatef(x,y,z);

    glRotatef(yaw , 0,1,0);
    glRotatef(pitch, 1,0,0);
    glRotatef(roll, 0,0,1);

    if(deactiveCorner < 0)
    	//Square
		drawCube(width,height,length);
	else {
		//Triangle
		drawRightAngleTrianlgePrism(width,height,length, deactiveCorner);
	}

 	glPopMatrix();
}

bool TrackPiece::checkTraction(SpaceShip* ship){
	 if(ship->isJumping())
	 	//Ship is jumping no need to check traction
 		return false;

	float px = ship->getX();
	float pz = ship->getZ();

	//Caluclating landing y finding the x and z points distance from the square 
	//base for sloping
	float xdiff1 = px -x;
	float zdiff1 = pz -z;
	float diff1 = sqrt(xdiff1*xdiff1 + zdiff1*zdiff1 );

	float xdiff2 = hitX4 -px;
	float zdiff2 = hitZ4 -pz;
	float diff2 = sqrt(xdiff2*xdiff2 + zdiff2*zdiff2 );




	//Law of cosines
	float calc = (diff1*diff1+ diff3*diff3 - (diff2 * diff2))/ (2 * diff1 * diff3);
	float angle = 0;
	if(calc < 1)
		angle = invCos(calc);

	//Removing yaw from x and z calc
	float xs = diff1 * Sin(angle);
	float zs = diff1 * Cos(angle);


	float landingY =y + pitchSlope*zs + xs* rollSlope;
 
	//Checkingh hit detection 
	//Thanks to
	//http://math.stackexchange.com/questions/190111/how-to-check-if-a-point-is-inside-a-rectangle/190373#190373
	float areaSum = 0;
	switch(deactiveCorner){
		//Triangles
		case BOT_LEFT:
			areaSum = areaOfTrianlge(hitX2,hitZ2, hitX3, hitZ3, px,pz);
			areaSum += areaOfTrianlge(hitX3,hitZ3, hitX4, hitZ4, px,pz);
			areaSum += areaOfTrianlge(hitX4,hitZ4, hitX2, hitZ2, px,pz);
			break;
		case BOT_RIGHT:
			areaSum = areaOfTrianlge(hitX1,hitZ1, hitX3, hitZ3, px,pz);
			areaSum += areaOfTrianlge(hitX3,hitZ3, hitX4, hitZ4, px,pz);
			areaSum += areaOfTrianlge(hitX4,hitZ4, hitX1, hitZ1, px,pz);
			break;
		case TOP_RIGHT:
			areaSum = areaOfTrianlge(hitX1,hitZ1, hitX4, hitZ4, px,pz);
			areaSum += areaOfTrianlge(hitX4,hitZ4, hitX2, hitZ2, px,pz);
			areaSum += areaOfTrianlge(hitX2,hitZ2, hitX1, hitZ1, px,pz);
			break;
		case TOP_LEFT:
			areaSum = areaOfTrianlge(hitX1,hitZ1, hitX3, hitZ3, px,pz);
			areaSum += areaOfTrianlge(hitX3,hitZ3, hitX2, hitZ2, px,pz);
			areaSum += areaOfTrianlge(hitX2,hitZ2, hitX1, hitZ1, px,pz);
			break;
		//Squares
		default:
    		areaSum = areaOfTrianlge(hitX1,hitZ1, hitX4, hitZ4, px,pz);
			areaSum += areaOfTrianlge(hitX3,hitZ3, hitX4, hitZ4, px,pz);
			areaSum += areaOfTrianlge(hitX2,hitZ2, hitX3, hitZ3, px,pz);
			areaSum += areaOfTrianlge(hitX1,hitZ1, hitX2, hitZ2, px,pz);
			break;
	}
	
	if(fabs(areaSum - hitRectArea) >.3){
		return false; 
	}

	 //Checking that ship is close enough within y rangle
	if(ship->getY() > landingY+.1)
		return false; 
	if(ship->getY() < landingY-.5)
		return false;

	float shipYaw =ship->getYaw() -  yaw;
	ship->setPitch(Cos(shipYaw) *pitch + Sin(-shipYaw) * roll);
 	ship->setRoll(Sin(shipYaw) *pitch + Cos(shipYaw) * roll);



	ship->setLandingY(landingY);


	return true;
}
	
float TrackPiece::getX(){
	return x;
}

float TrackPiece::getY(){
	return y;
}

float TrackPiece::getZ(){
	return z;
}

void TrackPiece::setShiftAngle(float angle){
	shiftAngle = ToRad(angle);
}
