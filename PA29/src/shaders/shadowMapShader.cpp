#ifndef __SHADOW_MAP_SHADER_CPP_
#define __SHADOW_MAP_SHADER_CPP_

#include "shaders/shadowMapShader.h"

bool ShadowMapShader::FullInitAndLink() {
    if (!Initialize()) {
        printf("shadow map shader failed to init\n");
        return false;
    }
    if (!LoadShader(GL_VERTEX_SHADER, "../shaders/shadow_map_vertex.glsl")) {
        printf("shadow map vertex failed to init\n");
        return false;
    }
    if (!LoadShader(GL_FRAGMENT_SHADER, "../shaders/shadow_map_fragment.glsl")) {
        printf("shadow map vertex shader failed to init\n");
        return false;
    }
    if (!Finalize()) {
        printf("shader failed to finalize\n");
        return false;
    }
    if (!LinkShaderProps()) {
        printf("Shadow shader didn't find some variables\n");
        return false;
    }

    return true;
}

bool ShadowMapShader::LinkShaderProps() {
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

  // locate the g shadow map
  gShadowMap = GetUniformLocation("gShadowMap");
  if (gShadowMap == INVALID_UNIFORM_LOCATION) {
    printf("shadow map not found\n");
    return false;
  }

  return true;
}

#endif