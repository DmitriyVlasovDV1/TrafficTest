#version 420

#define LAND_SIZE 500
#define LAND_HEIGHT 65

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

layout(binding = 2) uniform sampler2D texHeight;

uniform float Time;
uniform mat4 MatrWVP;
uniform mat4 MatrW;
uniform vec3 TreePos;

out vec4 DrawColor;
out vec3 DrawPos;
out vec3 DrawNormal;
out vec2 DrawTexCoord;

vec3 GetNormal( vec2 TexCoord )
{
  float step = 0.015;

  int i, j;

  vec3 Tan, Right;
  DrawNormal = vec3(0, 1, 0);

  for (i = -1; i < 2; i++)
    for (j = -1; j < 2; j++)
    {
      if (i != 0 || j != 0)
      {
        Tan = vec3(i * step * LAND_SIZE,
                   (texture2D(texHeight, vec2(TexCoord.x + i * step, TexCoord.y + j * step)).x - texture2D(texHeight, TexCoord).x) * LAND_HEIGHT,
                   j * step * LAND_SIZE);
        Right = cross(Tan, vec3(0, 1, 0));
        DrawNormal += cross(Right, Tan);
      }
    }

  return normalize(DrawNormal);
}


float GetHeight( vec2 TexCoord )
{
  float step = 0.001;
  int i, j;

  float Height = 0;
  for (i = -1; i < 2; i++)
    for (j = -1; j < 2; j++)
      Height += texture2D(texHeight, vec2(TexCoord.x + i * step, TexCoord.y + j * step)).x * LAND_HEIGHT;

  return Height / 9;
}



/* Shader entry point */
void main( void )
{
//  vec3 Pos = (MatrW * vec4(InPosition, 1)).xyz;
  vec2 TreeMapPos = vec2(TreePos.z / LAND_SIZE + 0.5, TreePos.x / LAND_SIZE + 0.5);
  vec3 Vy = GetNormal( TreeMapPos );

  vec3 Vx = normalize(cross(Vy, vec3(0, 0, 1)));
  vec3 Vz = normalize(cross(Vy, Vx));

  mat4 NewWorld = mat4( Vx.x, Vx.y, Vx.z, 0,
                        Vy.x, Vy.y, Vy.z, 0,
                        Vz.x, Vz.y, Vz.z, 0, 
                        0,    0,    0,    1 );

  gl_Position = MatrWVP * (NewWorld * vec4(InPosition.x,
                                          InPosition.y + GetHeight(TreeMapPos), 
                                          InPosition.z + (InPosition.y > 10 ? sin(Time) * 0.15 * (InPosition.y - 10) : 0), 1));

  DrawColor = InColor;
  DrawNormal = normalize(transpose(inverse(mat3(NewWorld * MatrW))) * InNormal);
  DrawPos = (MatrW * vec4(InPosition, 1)).xyz;
  DrawTexCoord = InTexCoord;

} /* End of 'main' function */
