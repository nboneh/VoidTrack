 #include "VoidTrack.h"

float frand(float rng,float off)
{
   return rand()*rng/RAND_MAX+off;
}


float areaOfTrianlge(float x1,float y1,float x2,float y2,float x3,float y3){
	//Based on the shoelace formula
	return fabs((x1*y2+ x2*y3 +x3*y1 -x1*y3- x3*y2 -x2*y1)/2);
}