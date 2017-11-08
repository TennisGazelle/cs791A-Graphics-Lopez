//
// Created by Daniel Lopez on 10/26/17.
//

#include "shaders/skyboxShader.h"

bool SkyboxShader::FullInitAndLink() {
    if (!Initialize()) {
        printf("shader failed to init\n");
        return false;
    }
    if (!LoadShader(GL_VERTEX_SHADER, "../shaders/skybox_vertex.glsl")) {
        printf("Vertex Shader failed to Initialize\n");
        return false;
    }
    if (!LoadShader(GL_FRAGMENT_SHADER, "../shaders/skybox_fragment.glsl")) {
        printf("Fragment Shader failed to Initialize\n");
        return false;
    }
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

bool SkyboxShader::LinkShaderProps() {
    mvpMatrix = GetUniformLocation("MVP");
    if (mvpMatrix == INVALID_UNIFORM_LOCATION) {
        printf("skybox mvp matrix not found\n");
        return false;
    }
    return true;
}