#version 420

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

uniform vec3 CamLoc;
uniform mat4 MatrWVP;

out vec3 DrawPosition;

/* Shader entry point */
void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition + CamLoc, 1);
  DrawPosition = InPosition;

} /* End of 'main' function */
