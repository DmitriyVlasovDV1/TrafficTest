#version 420
layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform sampler2D TexWater;

in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;
in vec2 DrawTexCoord;

void main( void )
{
  float TexSize = 15;
  OutColor = texture2D(TexWater, DrawTexCoord * TexSize);
  OutColor.w = 0.3;
}