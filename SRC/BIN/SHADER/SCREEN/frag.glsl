#version 420

layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform sampler2D MainTex;
layout(binding = 1) uniform sampler2D DepthTex;


uniform float Time;

in vec2 DrawTexCoord;

/* Shader entry point */
void main( void )
{
  OutColor = texture(MainTex, DrawTexCoord);
    
} /* End of 'main' function */
