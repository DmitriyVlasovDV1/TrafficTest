#version 420


#define GRASS (vec4(0.0, 1.0, 0.0, 1.0))
#define STONE (vec4(1.0, 0.0, 1.0, 1.0))
#define DIRT (vec4(0.0, 1.0, 1.0, 1.0))
#define SAND (vec4(1.0, 1.0, 0.0, 1.0))

#define DELTA_GRASS (length(GRASS - material))
#define DELTA_STONE (length(STONE - material))
#define DELTA_DIRT (length(DIRT - material))
#define DELTA_SAND (length(SAND - material))


layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform sampler2D texMaterials;
layout(binding = 1) uniform sampler2D texGrass;
layout(binding = 2) uniform sampler2D texStone;
layout(binding = 3) uniform sampler2D texDirt;
layout(binding = 4) uniform sampler2D texSand;

in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;
in vec2 DrawTexCoord;

void main( void )
{
  float TexSize = 10;
  float BlurCoef = 0.002 * 1;
  vec4 material = texture2D(texMaterials, DrawTexCoord);

  float res = min(DELTA_GRASS, 
              min(DELTA_STONE,
              min(DELTA_DIRT,              
                  DELTA_SAND)));

  vec4 resTex = vec4(0);
  int i;
  int j;

  for (i = -1; i < 2; i++)
    for (j = -1; j < 2; j++)
    {
      if (res == DELTA_GRASS) {
         resTex += texture2D(texGrass, DrawTexCoord * TexSize + vec2(i, j) * BlurCoef);
      } else if (res == DELTA_STONE) {
        resTex += texture2D(texStone, DrawTexCoord * TexSize + vec2(i, j) * BlurCoef);
      } else if (res == DELTA_DIRT) {
        resTex += texture2D(texDirt, DrawTexCoord * TexSize + vec2(i, j) * BlurCoef);
      } else if (res == DELTA_SAND) {
        resTex += texture2D(texSand, DrawTexCoord * TexSize + vec2(i, j) * BlurCoef);
      } else {
        resTex = vec4(0.0, 0.0, 0.0, 0.0);
      }
    }
  
  OutColor = vec4(DrawNormal * 0.5 + vec3(0.5), 1);
  OutColor = resTex / 9;

  
}