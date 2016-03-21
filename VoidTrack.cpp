#include "VoidTrack.h"
#include "GameObjects/background.h"
#include "GameObjects/spaceship.h"
#include "GameObjects/track.h"

double dim=5.0;
int th=0;         //  Azimuth of view angle
int ph=30;         //  Elevation of view angle
double prevT = 0;
float counter = 0;


Background* background = NULL;
SpaceShip * spaceShip = NULL;
Track * track = NULL;



void idle()
{
    //  Elapsed time in seconds
   double currentT = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   double t = currentT - prevT;

   if(counter >= 0)
      counter += t;

   if(counter >= 3.0){
     spaceShip->go();
     counter = -1;
   }


   spaceShip->update(t);
   track->checkTraction(spaceShip);
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

  float shipYaw = th - spaceShip->getYaw();
  float shipPitch = ph-spaceShip->getPitch();

  double Ex = (-2*dim*Sin(shipYaw)*Cos(shipPitch));
   double Ey = (+2*dim        *Sin(shipPitch));
   double Ez = (+2*dim*Cos(shipYaw)*Cos(shipPitch));

   float spaceShipY = spaceShip->getY() + spaceShip->getFloatingHeight();
   if(spaceShipY <= -10){
      spaceShipY = -10;
      spaceShip->stopMoving();
   }
   gluLookAt(Ex +spaceShip->getX() ,Ey+spaceShipY,Ez+ spaceShip->getZ() 
    , spaceShip->getX(),spaceShipY,spaceShip->getZ() 
   ,0,Cos(shipPitch),0);

   background->draw();
   spaceShip->draw();
  track->draw();

   //  Make scene visible
   glFlush();
   glutSwapBuffers();
   glutPostRedisplay();
}

void special_press(int key,int x,int y)
{
     //  Right arrow - increase rotation by 5 degree
   if (key == GLUT_KEY_RIGHT)
    th -= 5;
   //  Left arrow - decrease rotation by 5 degree
   else if (key == GLUT_KEY_LEFT)
    th += 5;

   //  Up Arrow - increase rotation by 5 degree
   else if (key == GLUT_KEY_UP)
    ph += 5;
   //  Down Arrow - decrease rotation by 5 degree
   else if (key == GLUT_KEY_DOWN)
     ph -= 5;


}

void key_press(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);

    if(ch == 'a' || ch == 'A'){
      spaceShip->turnRight();
    } else if(ch == 'd' || ch == 'D'){
      spaceShip->turnLeft();
    } 

    //Space Bar
    else if(ch == 32){
      spaceShip->jump();
    }
}



void key_up(unsigned char ch, int x, int y){

    if(ch == 'a' || ch == 'A'){
      spaceShip->stopTurnRight();
    } else if(ch == 'd' || ch == 'D'){
      spaceShip->stopTurnLeft();
    }
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

   glutFullScreen();  
   background = new Background();
   spaceShip = new SpaceShip();
   track = new Track();
   
   //  Register display, reshape, and key callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special_press);
   glutSpecialUpFunc(special_press);
   glutKeyboardFunc(key_press);
   glutKeyboardUpFunc(key_up);
   glutIdleFunc(idle);
   glEnable(GL_DEPTH_TEST);

   //  Pass control to GLUT for events
   glutMainLoop();
   //  Return to OS
   return 0;
}
