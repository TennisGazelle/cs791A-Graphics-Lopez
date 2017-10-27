//
// Created by Daniel Lopez on 10/26/17.
//

#include "shaders/skyboxShader.h"

bool SkyboxShader::LinkShaderProps() {
    mvpMatrix = GetUniformLocation("MVP");
    if (mvpMatrix == INVALID_UNIFORM_LOCATION) {
        printf("skybox mvp matrix not found\n");
        return false;
    }
    return true;
}