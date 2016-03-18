#include "VoidTrack.h"
#include "GameObjects/background.h"
#include "GameObjects/spaceship.h"

double dim=5.0;
int th=0;         //  Azimuth of view angle
int ph=20;         //  Elevation of view angle
double prevT = 0;
float counter = 0;

unsigned int BACKGROUND;

Background* background;
SpaceShip * spaceShip;


void idle()
{
    //  Elapsed time in seconds
   double currentT = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   double t = currentT - prevT;

   counter += t;

   if(counter >= 1.0){
      spaceShip->go();
   }

   spaceShip->update(t);
   prevT = currentT;
   glutPostRedisplay();
}



void display()
{
   //  Clear screen

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

//  glEnable(GL_DEPTH_TEST);
 // glEnable(GL_LIGHTING);
  //glEnable(GL_NORMALIZE);

   //Setting camera around spaceship
   glLoadIdentity();

   float tempTh = th;  //- spaceShip->getYaw();
   //float tempPh = ph -
   double Ex = (-2*dim*Sin(tempTh)*Cos(ph));
   double Ey = (+2*dim        *Sin(ph));
   double Ez = (+2*dim*Cos(tempTh)*Cos(ph));
   gluLookAt(Ex +spaceShip->getX() ,Ey+spaceShip->getY(),Ez+ spaceShip->getZ() 
    , spaceShip->getX(),spaceShip->getY(),spaceShip->getZ() 
    , 0,Cos(ph),0);

   background->draw();
   spaceShip->draw();


   //  Make scene visible
   glFlush();
   glutSwapBuffers();
   glutPostRedisplay();
}

void special(int key,int x,int y)
{
     //  Right arrow - increase rotation by 5 degree
   if (key == GLUT_KEY_RIGHT)
    th += 5;
   //  Left arrow - decrease rotation by 5 degree
   else if (key == GLUT_KEY_LEFT)
    th -= 5;

   //  Up Arrow - increase rotation by 5 degree
   else if (key == GLUT_KEY_UP)
    ph -= 5;
   //  Down Arrow - decrease rotation by 5 degree
   else if (key == GLUT_KEY_DOWN)
     ph += 5;

   glutPostRedisplay();

}

void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}



void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
    double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   Project(55, w2h, dim);
}



/*
 * GLUT based Hello World
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered true color window with Z-buffer
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   glutInitWindowSize(600, 600);
   //  Create window
   glutCreateWindow("VoidTrack");

    BACKGROUND = LoadTexBMP("textures/background.bmp");
   glutFullScreen();  
   //  Register display, reshape, and key callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   glEnable(GL_DEPTH_TEST);

   background = new Background();
   spaceShip = new SpaceShip();

   //  Pass control to GLUT for events
   glutMainLoop();
   //  Return to OS
   return 0;
}
