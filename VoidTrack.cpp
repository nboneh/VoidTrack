#include "VoidTrack.h"
#include "GameObjects/background.h"
#include "GameObjects/spaceship.h"
#include "GameObjects/track.h"
#include "GameObjects/counter.h"


static const char* Shader_Attribs_Flame[] = {"","","","","Vel","DurationTime", NULL};
static const char* Shader_Attribs_Track[] = { "","","","","","","","Shifts", NULL};

float baseElevation = 20;
double dim=5.0;
float azimuth=0;         //  Azimuth of view angle
float elevation=baseElevation;         //  Elevation of view angle
double prevT = 0;
bool setAtFinalCam = false;
bool gameOver = false;
bool paused = false;
bool startedShip = false;
bool won = false;
float camdist =dim * 1.5;
double t;
int ambient   =  45;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)

float camAngRate = 200;
float colorTransRate = .3;
//A simple lighting shader for what ever object needs to draw itself without a shader
int SIMPLE_LIGHTING_SHADER ;
unsigned int BACKGROUND_TEXTURE;
int FLAME_SHADER;
unsigned int CLICK_ON_SOUND;
unsigned int CLICK_OFF_SOUND;
unsigned int JUMP_SOUND;
unsigned int COUNT_DOWN_SOUND;
unsigned int GAME_OVER_SOUND;
unsigned int WIN_SOUND;
unsigned int MUSIC;
unsigned int SPACESHIP_OBJ;

double w2h ;


int totalLaps = 6;
int currentLap = 0;

float finalCameraX ;
float finalCameraY ; 
float finalCameraZ;

Background* background;
SpaceShip * spaceShip;
Track * track;
Counter *counter;

int TrackShaders[6];
int numOfColors = 12;
//Current Color pallet
//m is main
//p is prime
//b is back
//g is green
//and then rgb
// mpr, mpg, mpb;
// mcr, mcg, mcb;
// bpr, bpg, bpb;
// bcr, bcg, bcb;
float colors[12];

float transColors[] = {0,0,0,0,0,0,0,0,0,0,0,0};

 void addLighting(){
    //  Translate intensity to color vectors
   float Ambient[]   = {0.01f*ambient ,0.01f*ambient ,0.01f*ambient ,1.0};
   float Diffuse[]   = {0.01f*diffuse ,0.01f*diffuse ,0.01f*diffuse ,1.0};
   float Specular[]  = {0.01f*specular,0.01f*specular,0.01f*specular,1.0};
   float Postion[] = {0,55,0};
   //  Light position

    //  Draw light position as ball (still no lighting here)
   //  OpenGL should normalize normal vectors
   glEnable(GL_NORMALIZE);
   //  Enable lighting
   glEnable(GL_LIGHTING);
   //  glColor sets ambient and diffuse color materials
   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   //  Enable light 0
   glEnable(GL_LIGHT0);
   //  Set ambient, diffuse, specular components and position of light 0
   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
   glLightfv(GL_LIGHT0,GL_POSITION,Postion);
}
void resetColors(){
     spaceShip->setColor(0, 0, 0, 0, 0, 0);
  track->setColor(0,0,0,0,0,0);
  background->setColor(0,0,0);
}
bool updateColors(double t){
     bool update = false;
  
  for(int i = 0; i <numOfColors; i++){
     if(transColors[i] < colors[i]){
        update = true;
        transColors[i] += colorTransRate * t;
        if(transColors[i] >= colors[i])
            transColors[i] = colors[i];
     }

    if(transColors[i] > colors[i]){
        update = true;
        transColors[i] -= colorTransRate * t;
        if(transColors[i] <= colors[i])
            transColors[i] = colors[i];
     }
  }
  if(update){
    spaceShip->setColor(transColors[0], transColors[1], transColors[2], transColors[3], transColors[4], transColors[5]);
     track->setColor(transColors[6], transColors[7], transColors[8], transColors[9], transColors[10], transColors[11]);
     track->setStartLineColor(transColors[3], transColors[4], transColors[5]);
     background->setColor(transColors[9],transColors[10],transColors[11]);
  }
  return update;
}

void updateLap(){
  currentLap = track->getLap();
  if(won)
    return;
  if(currentLap > totalLaps){
    won = true;
    playSound(WIN_SOUND, false);
    stopSound(MUSIC);
    spaceShip->stop();
  }
  switch(currentLap){
    case 0:
    case 1:
      //Red main
    colors[0] = 220/255.0;
    colors[1] =  20/255.0;
    colors[2] = 30/255.0;

    colors[3] = 178/255.0;
    colors[4] =  34/255.0;
    colors[5] = 34/255.0;

      //Green back
      colors[6] = 50/255.0;
      colors[7] = 205/255.0;
      colors[8]= 50/255.0;

     colors[9] = 34/255.0;
      colors[10] = 139/255.0;
      colors[11]= 34/255.0;

      break; 
    case 2:
      //Orange main
    colors[0] = 255/255.0;
    colors[1] =  100/255.0;
    colors[2] = 0/255.0;

    colors[3] = 255/255.0;
    colors[4] =  70/255.0;
    colors[5] = 0/255.0;

      //Blue back
      colors[6] = 65/255.0;
      colors[7] = 105/255.0;
      colors[8]= 225/255.0;

     colors[9] = 0/255.0;
      colors[10] = 0/255.0;
      colors[11]= 139/255.0;

      break; 

    case 3:
      //Purple main
    colors[0] = 128/255.0;
    colors[1] =  0/255.0;
    colors[2] = 128/255.0;

    colors[3] = 75/255.0;
    colors[4] =  0/255.0;
    colors[5] = 130/255.0;

      //Yellow back
      colors[6] = 255/255.0;
      colors[7] = 255/255.0;
      colors[8]= 0/255.0;

     colors[9] = 204/255.0;
      colors[10] = 204/255.0;
      colors[11]= 0/255.0;

      break; 

          case 4:

      //Yellow main
      colors[0] = 255/255.0;
      colors[1] = 255/255.0;
      colors[2]= 0/255.0;

     colors[3] = 204/255.0;
      colors[4] = 204/255.0;
      colors[5]= 0/255.0;

          //Purple back
    colors[6] = 128/255.0;
    colors[7] =  0/255.0;
    colors[8] = 128/255.0;

    colors[9] = 75/255.0;
    colors[10] =  0/255.0;
    colors[11] = 130/255.0;

      break; 


    case 5:
          //Blue main
      colors[0] = 65/255.0;
      colors[1] = 105/255.0;
      colors[2]= 225/255.0;

     colors[3] = 0/255.0;
      colors[4] = 0/255.0;
      colors[5]= 139/255.0;

      //Orange back

        colors[6] = 255/255.0;
    colors[7] =  100/255.0;
    colors[8] = 0/255.0;

    colors[9] = 255/255.0;
    colors[10] =  70/255.0;
    colors[11] = 0/255.0;

      break; 
    case 6:


      //Red main
      colors[0] = 50/255.0;
      colors[1] = 205/255.0;
      colors[2]= 50/255.0;

     colors[3] = 34/255.0;
      colors[4] = 139/255.0;
      colors[5]= 34/255.0;
       //Green back
    colors[6] = 220/255.0;
    colors[7] =  20/255.0;
    colors[8] = 30/255.0;

    colors[9] = 178/255.0;
    colors[10] =  34/255.0;
    colors[11] = 34/255.0;
    break;


  }
  int shaderIndex = currentLap -1;
  if(shaderIndex < 0)
      shaderIndex = 0;
    if(currentLap != 1){
      //There is lap[0] update don't reupdate
      track->setShader(TrackShaders[shaderIndex]);
    }
  if(currentLap > 1){
    spaceShip->increaseTerminalVelocityBy(2);
  }
}


void reset(){
  spaceShip->reset();
  track->reset();
  counter->reset();
  setAtFinalCam = false;
  gameOver = false;
  startedShip = false;
  won = false;
  currentLap = 1;
  for(int i = 0; i <numOfColors; i++){
    transColors[i] = 0;
  }
  resetColors();
  updateLap();

}

void printLap(){
  glPushMatrix();
  glTranslatef(-5, -4.9,0);
  glScalef(1/200.0, 1/200.0, 1/200.0);
  glColor3f(transColors[0],transColors[1],transColors[2]);
  int lap = currentLap;
  if(lap <= 0)
    lap = 1;
  Print("Zones %d/%d", lap,totalLaps);

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
   t = currentT - prevT;

   if(t >= .2){
    //lag
    prevT =currentT;
    return;
   }

   if(!paused){
    if(!updateColors(t))
        counter->update(t);
    if(!startedShip && counter->startShip()){
      spaceShip->go();
      startedShip = true;
    }
    track->checkTraction(spaceShip);
    spaceShip->update(t);
    track->update(t);
    if(spaceShip-> fallen()){
      if(!gameOver){
        playSound(GAME_OVER_SOUND, false);
        stopSound(MUSIC);
      }
      gameOver = true;
    }
    if(track->getLap() >currentLap )
        updateLap();
  }
   prevT = currentT;
}


void display()
{
   //  Clear screen

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
   //Setting camera around spaceship
   
glLoadIdentity();

   float cameraYaw = - spaceShip->getYaw();
   float cameraPitch = -spaceShip->getPitch();


  double Ex = -(camdist*Sin(cameraYaw)*Cos(cameraPitch));
   double Ey = (camdist       *Sin(cameraPitch));
   double Ez = (camdist*Cos(cameraYaw)*Cos(cameraPitch));


    float cameraX = spaceShip->getX();
    float cameraY = spaceShip->getY()+ spaceShip->getFloatingHeight();
    float cameraZ = spaceShip->getZ();

   //If spaceship is out of bound of the track lost
   if( gameOver && !setAtFinalCam){
      finalCameraX = cameraX;
      finalCameraY = cameraY;
      finalCameraZ = cameraZ;
      setAtFinalCam = true;
   }

   if(setAtFinalCam){
     cameraX = finalCameraX;
      cameraY = finalCameraY;
      cameraZ = finalCameraZ;
   }
   glTranslatef(0,0,-camdist);
   glRotatef(elevation,1,0,0);
     glRotatef(azimuth,0,1,0);
    glTranslatef(0,0,camdist);
float * upVector = spaceShip->getUpVector();
   gluLookAt(Ex +cameraX ,Ey+cameraY,Ez+ cameraZ 
    , cameraX,cameraY,cameraZ  
   ,upVector[0],upVector[1],upVector[2]);
   free(upVector);

    //Drawing the scene
   background->draw();
   addLighting();
   spaceShip->draw();
  track->draw();
      //Displaying UI elements
   glDisable(GL_LIGHTING);
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
    
   //  Make scene visible
   glFlush();
   glutSwapBuffers();
   glutPostRedisplay();
}

void special_press(int key,int x,int y)
{
  if(won || gameOver)
      return;

    if(paused){
   if (key == GLUT_KEY_RIGHT){
      azimuth += t*camAngRate;
  }
   else if (key == GLUT_KEY_LEFT){
     azimuth -= t*camAngRate;
  }

   else if (key == GLUT_KEY_UP){
   elevation -= t*camAngRate;
   if(elevation<= -45)
         elevation = -45;
  }
   else if (key == GLUT_KEY_DOWN){
      elevation += t*camAngRate ;
     if(elevation>= 45)
      elevation = 45;
  }


}
  else 
  {
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
     if(paused)
          return;
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
        if(paused)
          return;
        spaceShip->setupJump();
    } else if(ch == 'p' || ch =='P'){
   
      if(gameOver || !counter->done() || won)
        //Conditions where one can't pause
        return;
      if(!paused){
        playSound(CLICK_ON_SOUND,false);
        pauseSound(MUSIC);
        paused = true;
      } else {
        playSound(CLICK_OFF_SOUND,false);
         playSound(MUSIC,true);
          paused = false;
          azimuth=0;   
          elevation=baseElevation;  
      }
    }

}

void key_press_up(unsigned char ch,int x,int y){
     if(paused)
          return;
      //Space Bar
   if(ch == 32){
        spaceShip->jump();
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
   // Setup OpenAl
   setupOpenAl();
   //  Request double buffered true color window with Z-buffer
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   glutInitWindowSize(600, 600);
   //  Create window
   glutCreateWindow("VoidTrack");
   glutFullScreen();  

  CLICK_ON_SOUND = loadSoundFile("sounds/clickon.wav", false);
  CLICK_OFF_SOUND = loadSoundFile("sounds/clickoff.wav", false);
  JUMP_SOUND = loadSoundFile("sounds/jump.wav", false);
  COUNT_DOWN_SOUND= loadSoundFile("sounds/countdown.wav", false);
  GAME_OVER_SOUND = loadSoundFile("sounds/gameover.wav", false);
  WIN_SOUND = loadSoundFile("sounds/win.wav", false);
  MUSIC = loadSoundFile("sounds/music.wav", true);
  SIMPLE_LIGHTING_SHADER=CreateShaderProg("shaders/lightingshader.vert","shaders/simpleshader.frag", NULL);
  BACKGROUND_TEXTURE = LoadTexBMP("textures/background.bmp");
  FLAME_SHADER = CreateShaderProg("shaders/flameshader.vert",NULL, (char **)Shader_Attribs_Flame);
  SPACESHIP_OBJ = LoadOBJ("spaceship.obj");

  TrackShaders[0] =CreateShaderProg("shaders/lightingshader2.vert","shaders/trackshader1.frag", (char **)Shader_Attribs_Track);
  TrackShaders[1] =   CreateShaderProg("shaders/lightingshader2.vert","shaders/trackshader2.frag", (char **)Shader_Attribs_Track);
  TrackShaders[2] =     CreateShaderProg("shaders/lightingshader2.vert","shaders/trackshader3.frag", (char **)Shader_Attribs_Track);
  TrackShaders[3] =    CreateShaderProg("shaders/lightingshader2.vert","shaders/trackshader4.frag", (char **)Shader_Attribs_Track);
  TrackShaders[4] =   CreateShaderProg("shaders/lightingshader2.vert","shaders/trackshader5.frag", (char **)Shader_Attribs_Track);
  TrackShaders[5] =    CreateShaderProg("shaders/lightingshader2.vert","shaders/trackshader6.frag", (char **)Shader_Attribs_Track);
  background = new Background();
  spaceShip = new SpaceShip();
  track = new Track();
  counter = new Counter();
  resetColors();
  updateLap();

  //  Register display, reshape, and key callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special_press);
  glutSpecialUpFunc(special_key_up);
  glutKeyboardFunc(key_press);
  glutKeyboardUpFunc(key_press_up);
  glutIdleFunc(idle);

  //  Pass control to GLUT for events
  glutMainLoop();

  closeOpenAL();
  free(spaceShip);
  free(track);
  free(background);
  free(counter);
  //  Return to OS
  return 0;
}
