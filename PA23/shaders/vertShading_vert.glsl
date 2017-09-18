#version 330
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec3 v_normal;

smooth out vec3 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform vec3 light;

void main(void) {
  vec3 vertInEyeSpace = vec3(mvMatrix * vec4(v_position, 1.0));
  vec3 normalInEyeSpace = vec3(mvMatrix * vec4(v_normal, 0.0));

  float distance = length (light - vertInEyeSpace);
  vec3 lightToVert = normalize(light - vertInEyeSpace);
  float diffuse = max(dot(normalInEyeSpace, lightToVert), 0.1);
  diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));

  gl_Position = mvpMatrix * vec4(v_position, 1.0);
  color =  v_color;
  color.r *= diffuse;
  color.g *= diffuse;
  color.b *= diffuse;
}
