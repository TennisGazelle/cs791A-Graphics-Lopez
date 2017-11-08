#version 330

layout (location = 0) in float  p_Type;
layout (location = 1) in vec3   p_Position;
layout (location = 2) in vec3   p_Velocity;
layout (location = 3) in float  p_Age;

out float Type0;
out vec3 Position0;
out vec3 Velocity0;
out float Age0;

void main() {
    Type0 = p_Type;
    Position0 = p_Position;
    Velocity0 = p_Velocity;
    Age0 = p_Age;
}