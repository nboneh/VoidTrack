#include "background.h"

void Background::update(double t){

}

void Background::draw(){
 	glPushMatrix();
 	glRotatef(90,0,0,0);
 	glScaled(500,500,500);
 	glEnable(GL_TEXTURE_2D);
  	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  	glBindTexture(GL_TEXTURE_2D,BACKGROUND);
	drawBall();
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
