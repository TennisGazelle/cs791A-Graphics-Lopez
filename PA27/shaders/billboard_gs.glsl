#version 330
layout (points)            in;
layout (triangle_strip)   out;
layout (max_vertices = 4) out;

uniform mat4 gVP;
uniform vec3 gCameraPos;

out vec2 uv;

void main() {
    vec3 vecPos = gl_in[0].gl_Position.xyz; // unique to the GS
        // access to each vertex that makes this primitive
        // gl_in is array of structs
    vec3 vecToCamera = normalize(gCameraPos - vecPos);
    vec3 up = vec3(0, 1, 0);
    vec3 right = normalize(cross(vecToCamera, up));

    // start drawing the quad
    // 0,0
    vecPos -= (right * 0.5);
    gl_Position = gVP * vec4(vecPos, 1.0);
    uv = vec2(0, 0);
    EmitVertex();

    // 1,0
    vecPos.y += 1.0;
    gl_Position = gVP * vec4(vecPos, 1.0);
    uv = vec2(0, 1);
    EmitVertex();

    // 1,0
    vecPos += right;
    vecPos.y -= 1.0;
    gl_Position = gVP * vec4(vecPos, 1.0);
    uv = vec2(1, 0);
    EmitVertex();

    // 1,1
    vecPos.y += 1.0;
    gl_Position = gVP * vec4(vecPos, 1.0);
    uv = vec2(1, 1);
    EmitVertex();

    EndPrimitive();
}