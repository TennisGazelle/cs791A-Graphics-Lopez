//
// Created by Daniel Lopez on 10/30/17.
//

#ifndef TUTORIAL_BILLBOARDSHADER_H
#define TUTORIAL_BILLBOARDSHADER_H


#include <shaders/shader.h>

class BillboardShader : public Shader {
public:
    BillboardShader();
    bool FullInitAndLink();
    bool LinkShaderProps();

    GLint vpMatrix; // view projection...
    GLint cameraPosition;
    GLint colorMap;
    GLint size;

};


#endif //TUTORIAL_BILLBOARDSHADER_H
