#version 330
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in vec2 v_texCoord;

smooth out vec4 color;
smooth out vec2 texCoord;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;

void main(void) {
	gl_Position = (mvpMatrix) * vec4(v_position, 1.0);
	texCoord = v_texCoord;
	color = vec4(v_color, 1.0);
}
