// Weird Wave 3
//  Colors
uniform vec3 ComplimentColor;
uniform vec3 PrimeColor;

//  Sets thickness of the line of the wave
const float WaveThickness = .1;

//  Model coordinates and light from vertex shader
varying float LightIntensity;
varying vec2  ModelPos;
uniform float time;
uniform float amp;

void main()
{
   vec3 color;

   //Subtracting time from x to make the wave move right and multiplying by 8 to increase the frequency
   float sinx = amp*sin( ModelPos.y + time*5.0);

   //If  z is in range of the value sinx function set the color to wave color otherwise set to background color 
   if(sinx >= (ModelPos.x - WaveThickness) && sinx <= (ModelPos.x + WaveThickness)  ){
      color = PrimeColor;
   } else {
      color = ComplimentColor;
   }


    //Subtracting time from x to make the wave move right and multiplying by 8 to increase the frequency
   float cosx = amp*sin( ModelPos.y + time*5.0 + 2.5) ;

   //If  z is in range of the value sinx function set the color to wave color otherwise set to background color 
   if(cosx >= (ModelPos.x - WaveThickness) && cosx <= (ModelPos.x + WaveThickness)  ){
      color = PrimeColor;
   } 

   //  Adjust color intensity for lighting (interpolated from vertex shader values)
   color *= LightIntensity;
   //  Pad color with alpha
   gl_FragColor = vec4(color,1.0);
}
