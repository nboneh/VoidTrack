#include "counter.h"

Counter::Counter(){
	scaleRate = 1;
	text = new char[3]; 
	reset();
}
void Counter::reset(){
	currentCount = 3;
	scale = .5;
	increasing = true;
	text[0] = '3';
	text[1] = '\0';
	started = false;
	playedMusic = false;
}

void Counter::update(double t){
	if(done())
		return;
	if(!started){
		playSound(COUNT_DOWN_SOUND, false);
		started = true;
	}
	if(increasing)
		scale += t* scaleRate;
	else 
		scale -= t* scaleRate;

	if(scale >= 1){
		scale = 1;
		increasing = false;
	
	} else if(scale <= .5) {
		scale = .5;
		increasing = true;
		currentCount--;

		if(currentCount > 0)
			sprintf(text,"%d", currentCount);
		else {
			text[0] = 'G';
			text[1] = 'O';
			text[2] = '!';
			text[3] = '\0';
			if(!playedMusic){
				playSound(MUSIC, true);
				playedMusic = true;
			}
		}
	}


}

void Counter::draw(){
	if(done() || !started)
		return;

	glPushMatrix();

	if(currentCount == 0){
		glTranslatef(0- scale/2, -scale/4,0);
	}
	else {
		glTranslatef(0 - scale/4, -scale/4,0);
	}
		glColor3f(.8,.8,0);
    glScalef(scale/152.0, scale/152.0, scale/152.0);
    Print(text);

	glPopMatrix();
}

bool Counter::startShip(){
	return currentCount <= 0;
	//return true;
}

bool Counter::done(){
	return currentCount <= -1;
	//return true;
}