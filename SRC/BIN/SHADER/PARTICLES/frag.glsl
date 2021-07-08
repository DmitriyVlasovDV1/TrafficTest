#version 420

layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform sampler2D Tex;

uniform float Trans;

in vec2 DrawTexCoord;

/* Shader entry point */
void main( void )
{
  OutColor = texture(Tex, DrawTexCoord);
  //ResTrans = 1 - length(DrawTexCoord * 2 - vec2(1, 1))) * Trans;
  if (length(DrawTexCoord * 2 - vec2(1, 1)) < 1)
    OutColor.w = Trans;
  else
    OutColor.w = 0;
  OutColor.w = Trans;

} /* End of 'main' function */
