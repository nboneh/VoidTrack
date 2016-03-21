#include "background.h"

Background::Background(){
	texture = LoadTexBMP("textures/background.bmp");
	reset();
}

void Background::reset(){
	r = 1;
	g = 1;
	b = 1;
}

void Background::draw(){
 	glPushMatrix();
 	glRotatef(90,0,0,0);
 	glScaled(500,500,500);
 	glColor3f(r,g,b);
 	glEnable(GL_TEXTURE_2D);
  	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  	glBindTexture(GL_TEXTURE_2D,texture);
	drawBall();
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Background::setColor(float _r,float _g,float _b){
	r = _r;
	g = _g;
	b = _b;
}