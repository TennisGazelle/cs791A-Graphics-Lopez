//
// Created by Daniel Lopez on 11/5/17.
//

#ifndef TUTORIAL_PSUPDATESHADER_H
#define TUTORIAL_PSUPDATESHADER_H


#include "shader.h"

class PSUpdateShader : public Shader {
public:
    PSUpdateShader();

    virtual bool FullInitAndLink();
    virtual bool LinkShaderProps();

    GLint deltaTimeMillis;
    GLint randomTexture;
    GLint time;
    GLint launcherLifetime;
    GLint shellLifetime;
    GLint secondaryShellLifetime;
};


#endif //TUTORIAL_PSUPDATESHADER_H
