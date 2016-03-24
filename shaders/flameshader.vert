uniform   float time;  //  Time
attribute float DurationTime; //  Start time
attribute vec3  Vel;   //  Velocity

void main(void)
{
   //  Particle location
   vec4 vert = gl_Vertex;
   //  Time offset mod v
   float t = mod(time,DurationTime);
   //  Particle color
   gl_FrontColor = gl_Color;
   //  Particle trajectory
   vert  += t*vec4(Vel,0);
   //  Transform particle location
   gl_Position = gl_ModelViewProjectionMatrix*vert;
}
