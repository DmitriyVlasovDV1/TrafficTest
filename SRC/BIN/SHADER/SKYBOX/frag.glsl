#version 420

layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform samplerCube Skybox;

in vec3 DrawPosition;
uniform float Time;

/* Shader entry point */
void main( void )
{
  float t = 0.5 + 0 * sin(Time) * 0.5 + 0.5; 
  vec3 TexCoord = vec3(DrawPosition.x, -DrawPosition.y, DrawPosition.z);
  OutColor = texture(Skybox, TexCoord) * t + vec4(DrawPosition, 1) * (1 - t);

//  OutColor = vec4(1, 0, 0, 1);
} /* End of 'main' function */
