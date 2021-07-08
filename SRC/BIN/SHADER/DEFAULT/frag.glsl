#version 420

layout(location = 0) out vec4 OutColor; // --> gl_FragColor;


uniform float Time;

in vec3 DrawNormal;

/* Shader entry point */
void main( void )
{
  OutColor = vec4(DrawNormal, 0.50);
} /* End of 'main' function */
