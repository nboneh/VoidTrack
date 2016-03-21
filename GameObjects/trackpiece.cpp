#include "trackpiece.h"

TrackPiece::TrackPiece(float _x, float _y, float _z, float _width, 
				 float _length, float _roll, float _pitch, float _yaw){

	trackHeight = .2;
	x = _x;
	y = _y;
	z = _z;
	width = _width;
	length = _length;
	roll = _roll;
	pitch = _pitch;
	yaw = _yaw;
	
	float xcalc1 = width * Cos(roll) * Cos(-yaw);
	float xcalc2 = length * Sin(-yaw);

	float zcalc1 = length * Cos(pitch) * Cos(-yaw);
	float zcalc2 = width * Sin(-yaw);

	hitX1 = x;
	hitZ1 = z;

	hitX2 = x + xcalc1;
	hitZ2 = z + zcalc2;

	hitX3 = x + xcalc1 + xcalc2; 
	hitZ3 = z - zcalc1 + zcalc2;

	hitX4 = x + xcalc2;
	hitZ4 = z - zcalc1;

	hitRectArea = areaOfTrianlge(hitX1, hitZ1, hitX2, hitZ2, hitX3, hitZ3);
	hitRectArea += areaOfTrianlge(hitX2, hitZ2, hitX3, hitZ3, hitX4, hitZ4);

	//Raise over run using soh coh toa
	pitchSlope = Tan(pitch);	
	rollSlope = Tan(roll);
}	

void TrackPiece::draw(){	

	glPushMatrix();

	glTranslatef(x,y,z);

    glRotatef(yaw , 0,1,0);
    glRotatef(pitch, 1,0,0);
    glRotatef(roll, 0,0,1);
	
	//Top
	glBegin(GL_QUADS);
	glNormal3f( 0,1, 0);
 	glVertex3f(0,0,0);
 	glVertex3f(width,0,0);
 	glVertex3f(width,0,-length);
 	glVertex3f(0,0,-length);
 	glEnd();

 	//Bottom
 	glBegin(GL_QUADS);
 	glNormal3f( 0,-1, 0);
 	glVertex3f(0,-trackHeight,0);
 	glVertex3f(width,-trackHeight,0);
 	glVertex3f(width,-trackHeight,-length);
 	glVertex3f(0,-trackHeight,-length);
 	glEnd();

 	//Left side
 	glBegin(GL_QUADS);
 	glNormal3f( -1,0, 0);
 	glVertex3f(0,-trackHeight,0);
 	glVertex3f(0,0,0);
 	glVertex3f(0,0,-length);
 	glVertex3f(0,-trackHeight,-length);
 	glEnd();

 	//Right side
 	glBegin(GL_QUADS);
 	glNormal3f(1,0, 0);
 	glVertex3f(width,-trackHeight,0);
 	glVertex3f(width,0,0);
 	glVertex3f(width,0,-length);
 	glVertex3f(width,-trackHeight,-length);
 	glEnd();

 	glPopMatrix();
}

bool TrackPiece::checkTraction(SpaceShip* ship){

	if(ship->getY() < y -1)
		return false;
	//Thanks to
	//http://math.stackexchange.com/questions/190111/how-to-check-if-a-point-is-inside-a-rectangle/190373#190373
	float px = ship->getX();
	float pz = ship->getZ();

	float areaSum = areaOfTrianlge(hitX1,hitZ1, hitX4, hitZ4, px,pz);
	areaSum += areaOfTrianlge(hitX3,hitZ3, hitX4, hitZ4, px,pz);
	areaSum += areaOfTrianlge(hitX2,hitZ2, hitX3, hitZ3, px,pz);
	areaSum += areaOfTrianlge(hitX1,hitZ1, hitX2, hitZ2, px,pz);
	
	if(!(fabs(areaSum - hitRectArea) < .01))
		return false; 

	//Setting y, roll, and pitch for ship according to the track piece
	float shipYaw =ship->getYaw() -  yaw;
	ship->setY(y + pitchSlope *fabs(pz - z) + rollSlope* fabs(px - x));

	ship->setPitch(Cos(shipYaw) *pitch + Sin(-shipYaw) * roll);
 	ship->setRoll(Sin(shipYaw) *pitch + Cos(shipYaw) * roll);


	return true;
}