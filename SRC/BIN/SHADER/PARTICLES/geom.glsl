/* FILE NAME: geom.glsl
 * PROGRAMMER: DV1
 * DATE: 19.09.2020
 * PURPOSE: 3D animation project.
 *          Geometry shader.
 */

#version 420

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 MatrVP;
uniform mat4 MatrW;
uniform vec3 Position;
uniform vec3 CamLoc;

uniform float Size;

out vec2 DrawTexCoord;

/* Shader entry point */
void main( void )
{
  vec3 Pos = (MatrW * vec4(Position, 1)).xyz;

  vec3 Dir = CamLoc - Pos;
  vec3 Right = normalize(cross(vec3(0, 1, 0), Dir));
  vec3 Up = normalize(cross(Dir, Right));

  DrawTexCoord = vec2(0, 1);
  gl_Position = MatrVP * vec4(Pos + (-Right + Up) * Size, 1);
  EmitVertex();

  DrawTexCoord = vec2(0, 0);
  gl_Position = MatrVP * vec4(Pos + (-Right + -Up) * Size, 1);
  EmitVertex();

  DrawTexCoord = vec2(1, 1);
  gl_Position = MatrVP * vec4(Pos + (Right + Up) * Size, 1);
  EmitVertex();

  DrawTexCoord = vec2(1, 0);
  gl_Position = MatrVP * vec4(Pos + (Right + -Up) * Size, 1);
  EmitVertex();
  
  EndPrimitive();
} /* End of 'main' function */


