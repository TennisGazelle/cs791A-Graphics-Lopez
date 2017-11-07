#version 330

uniform sampler2D gColorMap;

in vec2 uv;
out vec4 frag_color;

void main() {
//    frag_color = vec4(uv.x, uv.y, 0.0, 1.0);

    frag_color = texture(gColorMap, uv.xy);

    if (frag_color.r == 0 && frag_color.g == 0 && frag_color.b == 0) {
        discard;
    }
}