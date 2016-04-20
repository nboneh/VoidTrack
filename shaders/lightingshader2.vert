// This lighting shader will be used for the animated track platforms 

//  Light intensity and model position required by fragment shader
varying float LightIntensity;
varying vec2  ModelPos;

attribute vec2 Shifts;

// Center and zoom (for Mandelbrot set)
uniform vec3 loc;

//  Phong lighting intensity only
float phong()
{

  vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex); 
   vec3 L = normalize(gl_LightSource[0].position.xyz - P); 
   vec3 N = normalize(gl_NormalMatrix * gl_Normal);
//calculate Ambient Term:
vec4 Iamb = gl_FrontLightProduct[0].ambient;
Iamb = clamp(Iamb,0.0, 1.0);

//calculate Diffuse Term:
vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);
Idiff = clamp(Idiff,0.0, 1.0);


// write Total Color:
vec4 color =   Iamb + Idiff; 

   //  Vertex intensity
   return length(color.rgb) ;
}

void main()
{
   //  Scalar light intensity (for fragment shader)
   LightIntensity = phong();
   //  Save model coordinates (for fragment shader)
   ModelPos = gl_Vertex.xz - vec2(Shifts.x,Shifts.y);
   //  Return fixed transform coordinates for this vertex
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}