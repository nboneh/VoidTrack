//  Wave fragment shader

//  Colors
uniform vec3 ComplimentColor;
uniform vec3 PrimeColor;

//  Sets thickness of the line of the wave
const float WaveThickness = .1;

//  Model coordinates and light from vertex shader
varying float LightIntensity;
varying vec2  ModelPos;
varying float angleShift;
varying float radiusShift;
varying float varLenRelToTrack;
varying float zshift;

uniform float time;

void main()
{
    //x is the dependent and y is the independed reversing to make it less confusing
    //Converting to polar coordinates to be able to rotate the function
   float distAlongPath = abs(ModelPos.y - zshift)/varLenRelToTrack;
    float extAngle = 0.0;
   float r = sqrt(ModelPos.y*ModelPos.y+ ModelPos.x*ModelPos.x);

   float angle =  asin(ModelPos.x/r) + extAngle;
   vec3 color;


   //Subtracting time from x to make the wave move right and multiplying by 8 to increase the frequency
   float y = r*sin(angle )-radiusShift*sin(extAngle);
   float x = r*cos(angle);
   float on = y- (.8*sin((x/cos(extAngle)) -time*5.0));


   //If  z is in range of the value sinx function set the color to wave color otherwise set to background color 
   if(on < WaveThickness && on > 0.0){
      color = PrimeColor;
   } else {
      color = ComplimentColor;
   }

   //  Adjust color intensity for lighting (interpolated from vertex shader values)
   color *= LightIntensity;
   //  Pad color with alpha
   gl_FragColor = vec4(color,1.0);
}