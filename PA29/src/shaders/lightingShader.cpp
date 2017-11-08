#ifndef __LIGHTING_SHADER_CPP_
#define __LIGHTING_SHADER_CPP_

#include "shaders/lightingShader.h"

bool LightingShader::FullInitAndLink() {
    if (!Initialize()) {
        printf("Shader Failed to Initialize\n");
        return false;
    }
    // Add the vertex shader
    if (!LoadShader(GL_VERTEX_SHADER, "../shaders/simple_lighting_vertex.glsl")) {
        printf("Vertex Shader failed to Initialize\n");
        return false;
    }
    // Add the fragment shader
    if (!LoadShader(GL_FRAGMENT_SHADER, "../shaders/simple_lighting_fragment.glsl")) {
        printf("Fragment Shader failed to Initialize\n");
        return false;
    }
    // Connect the program
    if (!Finalize()) {
        printf("Program to Finalize\n");
        return false;
    }
    if (!LinkShaderProps()) {
        printf("Lighting shader didn't find some shaders\n");
        return false;
    }

    return true;
}

bool LightingShader::LinkShaderProps() {
    // Locate the projection matrix in the shader
    projectionMatrix = GetUniformLocation("projectionMatrix");
    if (projectionMatrix == INVALID_UNIFORM_LOCATION) {
        printf("projectionMatrix not found\n");
        return false;
    }

    // Locate the view matrix in the shader
    viewMatrix = GetUniformLocation("viewMatrix");
    if (viewMatrix == INVALID_UNIFORM_LOCATION) {
        printf("viewMatrix not found\n");
        return false;
    }

    // Locate the model matrix in the shader
    modelMatrix = GetUniformLocation("modelMatrix");
    if (modelMatrix == INVALID_UNIFORM_LOCATION) {
        printf("modelMatrix not found\n");
        return false;
    }

    // Locate the MV matrix
    mvMatrix = GetUniformLocation("mvMatrix");
    if (mvMatrix == INVALID_UNIFORM_LOCATION) {
        printf("mvMatrix not found\n");
        return false;
    }

    // Locate the MVP matrix
    mvpMatrix = GetUniformLocation("mvpMatrix");
    if (mvpMatrix == INVALID_UNIFORM_LOCATION) {
        printf("mvpMatrix not found\n");
        return false;
    }

    lightViewMatrix = GetUniformLocation("lightViewMatrix");
    if (lightViewMatrix == INVALID_UNIFORM_LOCATION) {
        printf("light view matrix not found\n");
        return false;
    }

    light = GetUniformLocation("light");
    if (light == INVALID_UNIFORM_LOCATION) {
        printf("light not found\n");
        return false;
    }

    gShadowMap = GetUniformLocation("gShadowMap");
    if (gShadowMap == INVALID_UNIFORM_LOCATION) {
        printf("shadow map in light shader not found \n");
        return false;
    }

    gSampler = GetUniformLocation("gSampler");
    if (gSampler == INVALID_UNIFORM_LOCATION) {
        printf("g Sampler in light shader not found\n");
        return false;
    }

    gNormalMap = GetUniformLocation("gNormalMap");
    if (gNormalMap == INVALID_UNIFORM_LOCATION) {
        printf("gNormalMap not found in light shader\n");
        return false;
    }
    return true;
}

#endif