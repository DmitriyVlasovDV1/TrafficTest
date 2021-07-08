/* FILE NAME: geom.glsl
 * PROGRAMMER: DV1
 * DATE: 19.09.2020
 * PURPOSE: 3D animation project.
 *          Geometry shader.
 */

#version 420

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

out vec2 DrawTexCoord;

/* Shader entry point */
void main( void )
{
  float n = 1; 

  DrawTexCoord = vec2(0, 1);
  gl_Position = vec4(-n, n, 0, 1);
  EmitVertex();

  DrawTexCoord = vec2(0, 0);
  gl_Position = vec4(-n, -n, 0, 1);
  EmitVertex();

  DrawTexCoord = vec2(1, 1);
  gl_Position = vec4(n, n, 0, 1);
  EmitVertex();

  DrawTexCoord = vec2(1, 0);
  gl_Position = vec4(n, -n, 0, 1);
  EmitVertex();
  


  EndPrimitive();
} /* End of 'main' function */


