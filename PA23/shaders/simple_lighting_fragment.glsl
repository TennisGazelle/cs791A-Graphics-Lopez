#version 330

smooth in vec3 color;
smooth in vec3 vPosInWorld;
smooth in vec3 vNormInWorld;
smooth in vec3 vertToCam;
smooth in vec3 vertToLight;

out vec4 frag_color;

uniform vec4 light;

void main(void) {
  vec4 MatAmbientColor = vec4(0.5, 0.5, 0.5, 1.0);
  vec4 MatDiffuseColor = vec4(color, 1.0);
  vec4 MatSpecularColor = vec4(0.3, 0.3, 0.3, 1.0);
  vec4 LightColor = vec4(1.0, 1.0, 1.0, 0.0);
  float LightPower = 50.0f;
  // vec3 diffuseAlbedo = color;
  // float specPower = 2.0f;
  // vec3 ambient = vec3(0.1);

  vec3 n = normalize(vNormInWorld);
  vec3 l = normalize(vertToLight);
  vec3 e = normalize(vertToCam);
  vec3 r = normalize(-reflect(l, n));
  float distance = length(vec3(light) - vPosInWorld);
  float cosTheta = clamp(dot(n, l), 0, 1);
  float cosAlpha = clamp(dot(e, r), 0, 1);

  // vec3 diffuse = clamp(max(dot(n, l), 0.0) * color, 0.0, 1.0);
  //vec3 specular = clamp(pow(max(dot(r, e), 0.0), specPower) * vec3(0.75), 0.0, 1.0);
  // vec3 specular = vec3(0.0);

  //frag_color = vec4(ambient + diffuse + specular, 1.0);
  //frag_color = vec4(color, 1.0);

  //frag_color = vec4(color.rgb, 1.0);
  frag_color =
    // ambient - for indirect lighting
    MatAmbientColor +
    // diffuse - color of the object
    MatDiffuseColor * LightColor * LightPower * cosTheta / (distance * distance) +
    // specular - reflective highlights
    MatSpecularColor * LightColor * LightPower * pow(cosAlpha, 2) / (distance * distance);
}
