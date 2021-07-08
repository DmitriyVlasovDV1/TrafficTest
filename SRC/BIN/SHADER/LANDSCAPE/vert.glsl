#version 420

#define LAND_SIZE 500
#define LAND_HEIGHT 65

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

layout(binding = 5) uniform sampler2D texHeight;

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
  float step = 0.001;

  vec3 Pos = vec3(InPosition.x, InPosition.y + texture2D(texHeight, InTexCoord).x * LAND_HEIGHT, InPosition.z);

  int i, j;

  vec3 Tan, Right;
  DrawNormal = vec3(0, 1, 0);

  for (i = -1; i < 2; i++)
    for (j = -1; j < 2; j++)
    {
      if (i != 0 || j != 0)
      {
        Tan = vec3(i * step * LAND_SIZE,
                   (texture2D(texHeight, vec2(InTexCoord.x + i * step, InTexCoord.y + j * step)).x - texture2D(texHeight, InTexCoord).x) * LAND_HEIGHT,
                   j * step * LAND_SIZE);
        Right = cross(Tan, vec3(0, 1, 0));
        DrawNormal += cross(Right, Tan);
      }
    }

  DrawNormal = normalize(DrawNormal);

  gl_Position = MatrWVP * vec4(Pos, 1);
 // gl_Position = MatrWVP * vec4(InPosition * 1, 1);
  DrawColor = InColor;
  //DrawNormal = normalize(transpose(inverse(mat3(MatrW))) * InNormal);
  DrawPos = (MatrW * vec4(Pos, 1)).xyz;
  DrawTexCoord = InTexCoord;

} /* End of 'main' function */
