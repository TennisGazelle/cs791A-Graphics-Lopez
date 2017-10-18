#ifndef __SHADOW_MAP_SHADER_CPP_
#define __SHADOW_MAP_SHADER_CPP_

#include "shadowMapShader.h"

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