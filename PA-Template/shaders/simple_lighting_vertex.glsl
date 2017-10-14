#version 330
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in vec2 v_uv;

smooth out vec3 color;
smooth out vec2 uv;

smooth out vec3 vPosInWorld;
smooth out vec3 vNormInWorld;
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

	// normal (in view space)
	//vNormInWorld = vec3(modelMatrix * vec4(v_normal, 0.0));
	vNormInWorld = mat3(modelMatrix) * v_normal;

	// vertex -> camera vector (in view space)
	//vertToCam = vec3(0, 0, 0) - vec3( modelMatrix * vec4(v_position, 1.0));
	vertToCam = - vPosInWorld;

	// vertex -> light (in view space)
	vertToLight = light.xyz - vPosInWorld;

	gl_Position = (mvpMatrix) * vec4(v_position, 1.0);
	color = v_color;
	uv = v_uv;
}
