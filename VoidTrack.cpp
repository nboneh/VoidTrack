#include "VoidTrack.h"
#include "GameObjects/background.h"
#include "GameObjects/spaceship.h"
#include "GameObjects/track.h"

double dim=5.0;
int th=0;         //  Azimuth of view angle
int ph=30;         //  Elevation of view angle
double prevT = 0;
float counter = 0;
bool setAtFinalCam = false;
bool gameOver = false;
bool paused = false;

float finalCameraX ;
float finalCameraY ; 
float finalCameraZ;

Background* background = NULL;
SpaceShip * spaceShip = NULL;
Track * track = NULL;


void reset(){
  background->reset();
  spaceShip->reset();
  track->reset();
  setAtFinalCam = false;
  gameOver = false;
  counter = 0;
}

void printGameOver(){

  glPushMatrix();
  glTranslatef(-1.9, .4,0);
  glScalef(1/152.0, 1/152.0, 1/152.0);
  glColor3f(1,0,0);
  Print("Game Over");
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-1.85, -.4,0);
  glScalef(1/300.0, 1/300.0, 1/300.0);
  glColor3f(1,1,1);
  Print("Press space to retry");
  glPopMatrix();

}

void printPause(){

  glPushMatrix();
  glTranslatef(-1.5, .4,0);
  glScalef(1/152.0, 1/152.0, 1/152.0);
  glColor3f(1,0,0);
  Print("Paused");
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-4, -.8,0);
  glScalef(1/300.0, 1/300.0, 1/300.0);
  glColor3f(1,1,1);
  Print("Use the arrow keys to look around");
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-2.6, -1.5,0);
  glScalef(1/300.0, 1/300.0, 1/300.0);
  glColor3f(1,1,1);
  Print("Press space to resume");
  glPopMatrix();

 glPushMatrix();
  glTranslatef(-2.3, -2.2,0);
  glScalef(1/300.0, 1/300.0, 1/300.0);
  glColor3f(1,1,1);
  Print("Press escape to exit");
  glPopMatrix();
}



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

   if(!paused){
    spaceShip->update(t);
    track->checkTraction(spaceShip);
  }
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
   float cameraYaw = th - spaceShip->getYaw();
   float cameraPitch = ph-spaceShip->getPitch();

  double Ex = (-2*dim*Sin(cameraYaw)*Cos(cameraPitch));
   double Ey = (+2*dim        *Sin(cameraPitch));
   double Ez = (+2*dim*Cos(cameraYaw)*Cos(cameraPitch));

    float cameraX = spaceShip->getX();
    float cameraY = spaceShip->getY() + spaceShip->getFloatingHeight();
    float cameraZ = spaceShip->getZ();

   //If spaceship is out of bound of the track lost
   if(!setAtFinalCam && cameraY <= -5){
      finalCameraX = cameraX;
      finalCameraY = cameraY;
      finalCameraZ = cameraZ;
      setAtFinalCam = true;
      gameOver = true;
   }

   if(setAtFinalCam){
     cameraX = finalCameraX;
      cameraY = finalCameraY;
      cameraZ = finalCameraZ;
   }

   gluLookAt(Ex +cameraX ,Ey+cameraY,Ez+ cameraZ 
    , cameraX,cameraY,cameraZ  
   ,0,Cos(cameraPitch),0);


   background->draw();
   spaceShip->draw();
  track->draw();
      //Displaying UI elements
   glDisable(GL_DEPTH_TEST);
     // glEnable(GL_BLEND);
  glPushMatrix();
  glTranslatef(cameraX, cameraY,cameraZ);

  glRotatef(-cameraYaw , 0,1,0);
  glRotatef(-cameraPitch , 1,0,0);
  if(gameOver)
    printGameOver();

  if(paused)
    printPause();


  glPopMatrix();
   glEnable(GL_DEPTH_TEST);
         //glDisable(GL_BLEND);
   //  Make scene visible
   glFlush();
   glutSwapBuffers();
   glutPostRedisplay();
}

void special_press(int key,int x,int y)
{
  if(gameOver)
      reset();
    if(paused){
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
  }else {
    // Turn ship right
   if (key == GLUT_KEY_RIGHT)
      spaceShip->turnRight();
   //  Turn ship left
   else if (key == GLUT_KEY_LEFT)
      spaceShip->turnLeft();
  }
}

void special_key_up(int key,int x,int y)
{
    // Turn ship right
   if (key == GLUT_KEY_RIGHT)
      spaceShip->stopTurnRight();
   //  Turn ship left
   else if (key == GLUT_KEY_LEFT)
      spaceShip->stopTurnLeft();
  
}

void key_press(unsigned char ch,int x,int y)
{

   //  Exit on ESC
   if (ch == 27){
      if(!paused){
        if(!gameOver)
          paused = true; 
      }
      else 
        exit(0);
    }

      //Space Bar
   if(ch == 32){
        if(gameOver){
          reset();
          return;
        }
        if(paused){
          paused = false;
          th=0;   
          ph=30;  
          return;
        }
        spaceShip->jump();
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
   glutSpecialUpFunc(special_key_up);
   glutKeyboardFunc(key_press);
   glutIdleFunc(idle);
   glEnable(GL_DEPTH_TEST);

   //  Pass control to GLUT for events
   glutMainLoop();
   //  Return to OS
   return 0;
}
