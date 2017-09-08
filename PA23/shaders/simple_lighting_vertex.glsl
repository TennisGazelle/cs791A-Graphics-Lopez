#version 330
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec3 v_normal;

smooth out vec3 color;

smooth out vec3 vPosInWorld;
smooth out vec3 vNormInCamera;
smooth out vec3 vertToCam;
smooth out vec3 vertToLight;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;
uniform vec4 light;

void main(void) {
	// position of vertex in world space
	vPosInWorld = vec3(modelMatrix * vec4(v_position, 1.0));

	// vertex -> camera vector (in camera space)
	vertToCam = vec3(0, 0, 0) - vec3(viewMatrix * modelMatrix * vec4(v_position, 1.0));

	// vertex -> light (in camera space)
	vertToLight = vec3(viewMatrix * light) + vertToCam;

	// vertex normal (in camera space)
	vNormInCamera = vec3(viewMatrix * modelMatrix * vec4(v_normal, 0.0));

	gl_Position = (mvpMatrix) * vec4(v_position, 1.0);
	color = v_color;
}
