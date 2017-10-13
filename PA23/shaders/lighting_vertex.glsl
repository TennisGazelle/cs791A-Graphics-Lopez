#version 330

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_tex_coord;
layout (location = 2) in vec3 v_normal;

uniform mat4 gMVP;
uniform mat4 gLightMVP;
uniform mat4 gModel;

out vec4 lightPosInWorld;

out vec3 pos0;
out vec2 texCoord0;
out vec3 normal0;

void main() {
  gl_Position = gMVP * vec4(v_pos, 1.0);

  lightPosInWorld = gLightMVP * vec4(v_pos, 1.0);

  pos0 = (gModel * vec4(v_pos, 1.0)).xyz;
  texCoord0 = v_tex_coord;
  normal0 = (gModel * vec4(v_normal, 0.0)).xyz;
}
