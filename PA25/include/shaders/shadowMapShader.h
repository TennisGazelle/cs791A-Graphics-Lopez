#ifndef __SHADOW_MAP_SHADER_H_
#define __SHADOW_MAP_SHADER_H_

#include "shader.h"

class ShadowMapShader : public Shader {
public:
    bool LinkShaderProps();
    
    GLint projectionMatrix;
    GLint viewMatrix;
    GLint modelMatrix;
    GLint mvMatrix;
    GLint mvpMatrix;

    GLint gShadowMap;
};

#endif