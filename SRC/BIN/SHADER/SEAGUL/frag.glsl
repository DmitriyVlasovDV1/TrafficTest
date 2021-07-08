#version 420

layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform sampler2D Texture0;

in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;
in vec2 DrawTexCoord;

uniform vec3 Ka, Kd, Ks;
uniform float Ph;
uniform float Trans;
uniform bool IsTexture;

uniform float Time;
uniform vec3 CamLoc;

vec3 Shade( vec3 P, vec3 N )
{
  vec3 color = vec3(0);
  vec3 V = normalize(P - CamLoc);
  vec3 L = normalize(vec3(1, 1, 1));

  N = normalize(N);

  // Ambient
  color += min(vec3(0.1), Ka / 20);

  // Duffuse
  float nl = dot(N, L);
  if (nl > 0)
  {
    vec3 diff = Kd * nl;
    if (IsTexture)
      diff *= texture(Texture0, DrawTexCoord).rgb;
    color += diff;

    // Specular
    vec3 R = reflect(V, N);
    float rl = dot(R, L);
    if (rl > 0)
      color += Ks * pow(rl, Ph);
  }
  return color;
}

/* Shader entry point */
void main( void )
{
  vec3 color = DrawColor.rgb * Shade(DrawPos, DrawNormal);
  OutColor = vec4(color, Trans); //.rgb vec4(color, 1);
//  OutColor = vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, 1);
} /* End of 'main' function */
