#include "VoidTrack.h"
#include "GameObjects/background.h"

double dim=5.0;
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
double prevT = 0;
double count =1;

float x;
float y;
float z;

unsigned int BACKGROUND;

Background* background;


void idle()
{
    //  Elapsed time in seconds
   double currentT = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   double t = currentT - prevT;

   count += t;
   if(count >= 1){
      x = (float)rand()/(float)(RAND_MAX);
      y = (float)rand()/(float)(RAND_MAX);
      z = (float)rand()/(float)(RAND_MAX);
      count -=1;
    }
   background->update(t);

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

   glLoadIdentity();
   double Ex = (-2*dim*Sin(th)*Cos(ph));
   double Ey = (+2*dim        *Sin(ph));
   double Ez = (+2*dim*Cos(th)*Cos(ph));
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);

    glColor3f(x,y,z);
   background->draw();
   glColor3f(1,1,1);
   drawCube();

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

   //  Pass control to GLUT for events
   glutMainLoop();
   //  Return to OS
   return 0;
}
