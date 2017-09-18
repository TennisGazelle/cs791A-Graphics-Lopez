#version 330
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec3 v_normal;

smooth out vec3 vertPosition;
smooth out vec4 vertColor;
smooth out vec3 vertNormal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

void main(void) {
	// vert position into eye space
	vertPosition = vec3(modelMatrix * vec4(v_position, 1.0));
	// pass through color
	vertColor = vec4(v_color, 1.0);
	// vert normal in eye space
	vertNormal = vec3(modelMatrix * vec4(v_normal, 0.0));

	gl_Position = (mvpMatrix) * vec4(v_position, 1.0);
}
