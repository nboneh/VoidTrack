//  Phong lighting

vec4 phong()
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
vec4 color =  Iamb + Idiff  ; 

   //  Vertex intensity
   return color;
}

void main()
{
   //  Vertex color (using Phong lighting)
   gl_FrontColor = phong();
   //  Texture coordinates
   gl_TexCoord[0] = gl_MultiTexCoord0;
   //  Return fixed transform coordinates for this vertex
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
