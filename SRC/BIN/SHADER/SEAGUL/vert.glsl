#version 420

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

uniform float Time;
uniform mat4 MatrWVP;
uniform mat4 MatrW;

out vec4 DrawColor;
out vec3 DrawPos;
out vec3 DrawNormal;
out vec2 DrawTexCoord;

/* Shader entry point */
void main( void )
{
  float swing = abs(InPosition.x) > 0.8 ? (sin(abs(InPosition.x) * 0.1 + Time * 4) * abs(InPosition.x) * 0.5) :
                -InPosition.z * sin(Time * 4) * 0.1;
  gl_Position = MatrWVP * vec4(InPosition.x, 
                               InPosition.y + swing, 
                               InPosition.z + (abs(InPosition.x) > 0.8 ? 0.2 : 0), 1);
 // gl_Position = MatrWVP * vec4(InPosition * 1, 1);
  DrawColor = InColor;
  DrawNormal = normalize(transpose(inverse(mat3(MatrW))) * InNormal);
  DrawPos = (MatrW * vec4(InPosition, 1)).xyz;
  DrawTexCoord = InTexCoord;

} /* End of 'main' function */
