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
  gl_Position = MatrWVP * vec4(InPosition.x + 1 * cos(InPosition.z * 0.1 + Time * 0.5) * 3, 
                               InPosition.y + 1 * sin(InPosition.z * 0.1 + Time * 2) * 1 , 
                               InPosition.z, 1);
  DrawColor = InColor;
  DrawNormal = normalize(transpose(inverse(mat3(MatrW))) * InNormal);
  DrawPos = (MatrW * vec4(InPosition, 1)).xyz;
  DrawTexCoord = InTexCoord;
  DrawTexCoord.x += sin(InPosition.z * 0.1 + Time * 2) * 0.002;

} /* End of 'main' function */
