//
// Created by Daniel Lopez on 10/26/17.
//

#ifndef TUTORIAL_SKYBOXSHADER_H
#define TUTORIAL_SKYBOXSHADER_H


#include "shader.h"

class SkyboxShader : public Shader {
public:
    bool FullInitAndLink();
    bool LinkShaderProps();
    GLint mvpMatrix;
private:

    GLuint textureLoc;
};


#endif //TUTORIAL_SKYBOXSHADER_H
