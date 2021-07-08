#version 420

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

uniform float Time;
uniform mat4 MatrWVP;

out vec3 DrawNormal;

/* Shader entry point */
void main( void )
{
 // gl_Position = MatrWVP * vec4(InPosition.x * sin(Time), InPosition.y * cos(Time), InPosition.z, 1);
  gl_Position = MatrWVP * vec4(InPosition.xyz, 1);

  DrawNormal = InNormal;
} /* End of 'main' function */
