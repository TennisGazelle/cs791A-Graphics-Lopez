#version 330

smooth in vec3 vertPosition;
smooth in vec4 vertColor;
smooth in vec3 vertNormal;

out vec4 frag_color;

uniform vec4 light;

void main(void) {
  float distance = length(vec3(light) - vertPosition);
  vec3 lightToVert = normalize(vec3(light) - vertPosition);
  float diffuse = max(dot(vertNormal, lightToVert), 0.1);
  diffuse = diffuse * (1.0/(1.0 + (0.25 * distance * distance)));

  frag_color = vertColor * diffuse;
  // if (distance < 1.72)
  // else
  //   frag_color = vec4(1.0);
}
