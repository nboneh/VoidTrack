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

	GLfloat *xzProjectModel = new GLfloat[16];

	glPushMatrix();
	glLoadIdentity();
    glRotatef(yaw , 0,1,0);
    glRotatef(pitch , 1,0,0);
    glRotatef(roll, 0,0,1);
	glGetFloatv(GL_MODELVIEW_MATRIX, xzProjectModel);
	glPopMatrix();

	hitX1 = x;
	hitZ1 = z;

	float zcalc1 = length *xzProjectModel[10];
	float zcalc2 = width * xzProjectModel[2];

	float xcalc1 = width *xzProjectModel[0];
	float xcalc2 = length *xzProjectModel[8];

	hitX2 = x + xcalc1;
	hitZ2 = z +zcalc2;

	hitX3 = x -xcalc2 +xcalc1; 
	hitZ3 = z  - zcalc1 +zcalc2;

	hitX4 = x  -xcalc2;
	hitZ4 = z - zcalc1;
	free(xzProjectModel);

	//The length of the projection in the z does not equal the length
	float xdiff3 = hitX4 -x;
	float zdiff3 = hitZ4 -z;
	diff3 = sqrt(xdiff3 * xdiff3 + zdiff3*zdiff3);

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

 	//To Check hit detection placement
 	 /*	glColor3f(0,1,0);
 	glBegin(GL_POLYGON);
 	glNormal3f(1,0, 0);
 	glVertex3f(hitX1,1,hitZ1);
 	glVertex3f(hitX2,1,hitZ2);
 	//glVertex3f(hitX3,1,hitZ3);
 	glVertex3f(hitX4,1,hitZ4);
 	glEnd();*/


//For pitch slope and roll slope modeling 
 	/*glColor3f(0,1,0);
 	glBegin(GL_POLYGON);
 	glNormal3f(1,0, 0);
 	glVertex3f(x,0+.1,z);
 	glVertex3f(x,pitchSlope*5+.1 ,z-5);
 	glVertex3f(x+5,pitchSlope*5 +.1+ rollSlope* 5,z-5);
 	glVertex3f(x+5,rollSlope *5+.1 ,z);
 	glEnd();
 	glColor3f(0,0,1);*/


 	glColor3f(0,0,1);
}

bool TrackPiece::checkTraction(SpaceShip* ship){

	if(ship->isJumping())
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
	float zs = diff1 * Cos(-angle);


	float landingY =y + pitchSlope*zs + xs* rollSlope;

	//Checking that ship is close enough within y rangle
	if(ship->getY() > landingY+.5)
		return false; 
	if(ship->getY() < landingY-.5)
		return false;

	//Checkingh hit detection 
	//Thanks to
	//http://math.stackexchange.com/questions/190111/how-to-check-if-a-point-is-inside-a-rectangle/190373#190373
	float areaSum = areaOfTrianlge(hitX1,hitZ1, hitX4, hitZ4, px,pz);
	areaSum += areaOfTrianlge(hitX3,hitZ3, hitX4, hitZ4, px,pz);
	areaSum += areaOfTrianlge(hitX2,hitZ2, hitX3, hitZ3, px,pz);
	areaSum += areaOfTrianlge(hitX1,hitZ1, hitX2, hitZ2, px,pz);
	
	if(!(fabs(areaSum - hitRectArea) < .001))
		return false; 

	//Setting y, roll, and pitch for ship according to the track piece
	float shipYaw =ship->getYaw() -  yaw;
	ship->setY(landingY);

	ship->setPitch(Cos(shipYaw) *pitch + Sin(-shipYaw) * roll);
 	ship->setRoll(Sin(shipYaw) *pitch + Cos(shipYaw) * roll);


	return true;
}
	

