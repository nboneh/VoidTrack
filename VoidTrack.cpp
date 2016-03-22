#include "VoidTrack.h"
#include "GameObjects/background.h"
#include "GameObjects/spaceship.h"
#include "GameObjects/track.h"
#include "GameObjects/counter.h"

double dim=5.0;
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
double prevT = 0;
bool setAtFinalCam = false;
bool gameOver = false;
bool paused = false;
bool startedShip = false;
bool won = false;
double w2h ;

int totalLaps = 6;
int currentLap = 1;

float finalCameraX ;
float finalCameraY ; 
float finalCameraZ;

Background* background;
SpaceShip * spaceShip;
Track * track;
Counter *counter;


void updateLap(){
  currentLap = track->getLap();
  if(currentLap > totalLaps){
    won = true;
    spaceShip->stop();
  }
}


void reset(){
  background->reset();
  spaceShip->reset();
  track->reset();
  counter->reset();
  setAtFinalCam = false;
  gameOver = false;
  startedShip = false;
  won = false;
  currentLap = 1;
}

void printLap(){
  glPushMatrix();
  glTranslatef(-5, -4.9,0);
  glScalef(1/200.0, 1/200.0, 1/200.0);
  glColor3f(1,1,1);
  Print("Lap %d/%d", currentLap,totalLaps);
  glPopMatrix();

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

}

void printWin(){
    glPushMatrix();
  glTranslatef(-1.9, .4,0);
  glScalef(1/152.0, 1/152.0, 1/152.0);
  glColor3f(1,0,0);
  Print("You Win");
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-3, -.4,0);
  glScalef(1/300.0, 1/300.0, 1/300.0);
  glColor3f(1,1,1);
  Print("Press space to play again");
  glPopMatrix();
}


void idle()
{
    //  Elapsed time in seconds
   double currentT = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   double t = currentT - prevT;


   if(!paused){
    counter->update(t);
    if(!startedShip && counter->startShip()){
      spaceShip->go();
      startedShip = true;
    }
    spaceShip->update(t);
    track->checkTraction(spaceShip);
    if(track->getLap() >currentLap )
        updateLap();
  }
   prevT = currentT;
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
   float cameraYaw = - spaceShip->getYaw();
   float cameraPitch = 30-spaceShip->getPitch();

  double Ex = (-2*dim*Sin(cameraYaw)*Cos(cameraPitch));
   double Ey = (+2*dim        *Sin(cameraPitch));
   double Ez = (+2*dim*Cos(cameraYaw)*Cos(cameraPitch));

    float cameraX = spaceShip->getX();
    float cameraY = spaceShip->getY() + spaceShip->getFloatingHeight();
    float cameraZ = spaceShip->getZ();

   //If spaceship is out of bound of the track lost
   if(!setAtFinalCam && cameraY <= -20){
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
  float * upVector = spaceShip->getUpVector();

   gluLookAt(Ex +cameraX ,Ey+cameraY,Ez+ cameraZ 
    , cameraX,cameraY,cameraZ  
   ,upVector[0],upVector[1]*Cos(cameraPitch),upVector[2]);
   free(upVector);

   glPushMatrix();
   //Setting pause camera angles
   glTranslatef(cameraX,cameraY,cameraZ);
   glRotatef(th,0,1,0);
  glRotatef(ph,1,0,0);
    glTranslatef(-cameraX,-cameraY,-cameraZ);
    //Drawing the scene
   background->draw();
   spaceShip->draw();
  track->draw();
  glPopMatrix();
      //Displaying UI elements
   glDisable(GL_DEPTH_TEST);


   glLineWidth(3);


glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();
glMatrixMode(GL_MODELVIEW);
glPushMatrix();
glLoadIdentity();
glScalef(1/dim-.02,1/dim -.02,1);


  if(gameOver)
    printGameOver();

  if(paused)
    printPause();

  if(!won)
    printLap();
  else 
    printWin();

  counter->draw();
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glPopMatrix();
   glEnable(GL_DEPTH_TEST);
    
   //  Make scene visible
   glFlush();
   glutSwapBuffers();
   glutPostRedisplay();
}

void special_press(int key,int x,int y)
{
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
    if(won || gameOver)
      return;
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
       exit(0);
    }

      //Space Bar
   if(ch == 32){
        if(gameOver || won){
          reset();
          return;
        }
        spaceShip->jump();
    } else if(ch == 'p' || ch =='P'){
   
      if(gameOver || !counter->done() || won)
        //Conditions where one can't pause
        return;
      if(!paused){
        paused = true;
      } else {
          paused = false;
          th=0;   
          ph=0;  
      }
    }

}




void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
     w2h = (height>0) ? (double)width/height : 1;
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

   //glutFullScreen();  
   
   background = new Background();
   spaceShip = new SpaceShip();
   track = new Track();
   counter = new Counter();

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
