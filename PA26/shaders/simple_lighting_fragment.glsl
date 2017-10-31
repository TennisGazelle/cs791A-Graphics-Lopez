#version 330

smooth in vec3 color;
smooth in vec2 uv;

smooth in vec4 lPosInWorld;
smooth in vec3 vPosInWorld;
smooth in vec3 vNormInWorld;
smooth in vec3 vTangInWorld;
smooth in vec3 vertToCam;
smooth in vec3 vertToLight;

out vec4 frag_color;

uniform vec4 light;
uniform sampler2D gSampler;
uniform sampler2D gShadowMap;
uniform sampler2D gNormalMap;

vec3 CalcBumpedNormal() {
    vec3 normal = normalize(vNormInWorld);
    vec3 tangent = normalize(vTangInWorld);
    tangent = normalize(tangent - dot(tangent, normal) * normal);
    vec3 bitangent = cross(tangent, normal);
    vec3 bumpMapNormal = texture(gNormalMap, uv).xyz;
    bumpMapNormal = 2.0* bumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 newNormal = mat3(tangent, bitangent, normal) * bumpMapNormal;
    return normalize(newNormal);
    return vec3(0.0);
}

float CalcShadowFactor(vec4 LightSpacePos) {
    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;
    vec3 UVCoords;
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
    UVCoords.z = 0.5 * ProjCoords.z + 0.5;
    float Depth = texture(gShadowMap, UVCoords.xy).x;
    if (Depth < UVCoords.z + 0.00001)
        return 0.0625;
    else
        return 1.0;
}

void main(void) {
  vec4 MatAmbientColor = vec4(0.001, 0.001, 0.001, 1.0);
  vec4 MatDiffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
  vec4 MatSpecularColor = MatDiffuseColor + vec4(0.3, 0.3, 0.3, 0.0);
  vec4 LightColor = vec4(1.0, 1.0, 1.0, 0.0);
  float LightPower = 50.0f;

  MatDiffuseColor = texture(gSampler, uv.xy);

  vec3 n = CalcBumpedNormal();
  vec3 l = normalize(vertToLight);
  vec3 e = normalize(vertToCam);
  vec3 r = normalize(-reflect(l, n));
  float distanceSquared = pow(length(vec3(light) - vPosInWorld), 2);
  float cosTheta = clamp(dot(n, l), 0, 1);
  float cosAlpha = clamp(dot(e, r), 0, 1);
  float shadowFactor = CalcShadowFactor(lPosInWorld);

  vec4 actualColor =
    // ambient - for indirect lighting
    MatAmbientColor +
    // diffuse - color of the object
    shadowFactor * (MatDiffuseColor * LightColor * LightPower * cosTheta / (distanceSquared) +
    // specular - reflective highlights
    MatSpecularColor * LightColor * LightPower * pow(cosAlpha, 2) / (distanceSquared));

  frag_color = (actualColor);
}
