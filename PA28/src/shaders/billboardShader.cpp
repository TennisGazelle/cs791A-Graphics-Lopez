//
// Created by Daniel Lopez on 10/30/17.
//

#include "shaders/billboardShader.h"

BillboardShader::BillboardShader() {

}

bool BillboardShader::FullInitAndLink() {
    if (!Initialize()) {
        printf("init billboard shader error\n");
        return false;
    }

    if (!LoadShader(GL_VERTEX_SHADER, "../shaders/billboard_vs.glsl") ||
        !LoadShader(GL_GEOMETRY_SHADER, "../shaders/billboard_gs.glsl") ||
        !LoadShader(GL_FRAGMENT_SHADER, "../shaders/billboard_fs.glsl")) {
        printf("billboard shader failed to load shaders from text");
        return false;
    }

    if (!Finalize()) {
        printf("error in billboard finalizing\n");
        return false;
    }

    if (!LinkShaderProps()) {
        printf("error in linking billboard shader\n");
        return false;
    }

    return true;
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

    size = GetUniformLocation("gSize");
    if (size == INVALID_UNIFORM_LOCATION) {
        printf("billboard shader didn't find size uniform\n");
        return false;
    }
    return true;
}