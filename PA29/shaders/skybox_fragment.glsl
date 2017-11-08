#version 330

in vec3 uv;

out vec4 frag_color;

uniform samplerCube gCubemapTexture;

void main() {
    frag_color = texture(gCubemapTexture, uv);
//    frag_color = vec4(uv, 1.0);
}