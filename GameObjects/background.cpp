#include "background.h"

void Background::draw(){
 	glPushMatrix();
 	glRotatef(90,1,0,0);
 	glScaled(500,500,500);
 	glColor3f(r,g,b);
 	glEnable(GL_TEXTURE_2D);
  	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  	glBindTexture(GL_TEXTURE_2D,BACKGROUND_TEXTURE);
	drawBall();
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Background::setColor(float _r,float _g,float _b){
	r = _r;
	g = _g;
	b = _b;
}