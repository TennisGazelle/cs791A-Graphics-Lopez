#version 330

struct BaseLight {
  vec3 color;
  float ambientIntensity;
  float diffuseIntensity;
}

struct Attenuation {
  float constant, linear, exp;
}

struct PointLight {
  BaseLight base;
  Attenuation atten;
  vec3 position;
}

// Fragment Shader out
out vec4 FragColor;

// Vertex Shader out
in vec4 lightPosInWorld;

in vec3 pos0;
in vec2 texCoord0;
in vec3 normal0;

// Uniforms
uniform sampler2D gSampler;
uniform sampler2D gShadowMap;
uniform vec3 gEyeWorldPos;
uniform float gMatSpeculatIntensity;

// calculate shadow factor of a pixel
  // multiply the result of our current light equation by this factor, and causes some attentuation of the lgiht in pixelsthat are determined to be shadows
float calcShadowFactor(vec4 lightSpacePos) {
  // perspective division
    // transfers the vector to NDC space
  vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
  // save them over
  vec2 uvCoords = vec2(
    0.5 * projCoords.x + 0.5,
    0.5 * projCoords.y + 0.5
  );
  float z = 0.5 * projCoords.z + 0.5;

  float depth = texture(gShadowMap, UVCoords).x;
  if (depth < z + 0.00001)
    return 0.5;
  else
    return 1.0;
}

vec4 calcLightGeneric(BaseLight light, vec3 lightDir, vec3 normal, float shadowFactor) {
    vec4 ambientColor = vec4(light.color * light.ambientIntensity, 1.0f);
    vec4 diffuseColor = vec4(0, 0, 0, 0);
    vec4 specularColor = vec4(0, 0, 0, 0);
    float diffuseFactor = dot(normal, -lightDir);

    if (diffuseFactor > 0) {
      diffuseColor = vec4(light.color * light.diffuseIntensity * diffuseFactor, 1.0f);

      // vert to eye
      vec3 vertToEye = normalize(gEyeWorldPos - pos0);
      vec3 reflect = normalize(reflect(lightDir, normal));
      float specFactor = dot(vertToEye, reflect);
      if (specFactor > 0) {
        specFactor = pow(specFactor, 2);
        //specFactor = vec4(light.color, 1.0f); // multiply by material specualt intensity and spec factor
      }
    }

    return ambientColor + shadowFactor * (diffuseColor + specularColor);
}

void main() {

}
