//
// Created by Daniel Lopez on 10/30/17.
//

#include "shaders/billboardShader.h"

BillboardShader::BillboardShader() {

}

bool BillboardShader::LinkShaderProps() {
    vpMatrix = GetUniformLocation("gVP");
    if (vpMatrix == INVALID_UNIFORM_LOCATION) {
        printf("billboard shader linking VP failed\n");
        return false;
    }

    cameraPosition = GetUniformLocation("gCameraPos");
    if (cameraPosition == INVALID_UNIFORM_LOCATION) {
        printf("billboard shader linking camera failed\n");
        return false;
    }

    colorMap = GetUniformLocation("gColorMap");
    if (colorMap == INVALID_UNIFORM_LOCATION) {
        printf("billboard shader didn't find color map uniform\n");
        return false;
    }
    return true;
}