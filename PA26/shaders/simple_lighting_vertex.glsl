#version 330
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in vec3 v_tangent;
layout (location = 4) in vec2 v_uv;

smooth out vec3 color;
smooth out vec2 uv;

smooth out vec4 lPosInWorld;
smooth out vec3 vPosInWorld;
smooth out vec3 vNormInWorld;
smooth out vec3 vTangInWorld;
smooth out vec3 vertToCam;
smooth out vec3 vertToLight;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;
uniform mat4 lightViewMatrix;
uniform vec4 light;

void main(void) {
	// position of vertex in world space
	vPosInWorld = vec3(modelMatrix * vec4(v_position, 1.0));

	// normal (in view space)
	vNormInWorld = mat3(modelMatrix) * v_normal;

	// tangent (in view space)
	vTangInWorld = mat3(modelMatrix) * v_tangent;

	// vertex -> camera vector (in view space)
	vertToCam = - vPosInWorld;

	// vertex -> light (in view space)
	vertToLight = light.xyz - vPosInWorld;

	gl_Position = (mvpMatrix) * vec4(v_position, 1.0);
	color = v_color;
	uv = v_uv;
	lPosInWorld = projectionMatrix * lightViewMatrix * modelMatrix * vec4(v_position, 1.0);
}
