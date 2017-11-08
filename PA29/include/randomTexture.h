//
// Created by Daniel Lopez on 11/5/17.
//

#ifndef TUTORIAL_RANDOMTEXTURE_H
#define TUTORIAL_RANDOMTEXTURE_H

#include "graphics_headers.h"


class RandomTexture {
public:
    RandomTexture();
    ~RandomTexture();

    bool Init(unsigned int size);
    void Bind(GLenum textureUnit);

private:
    GLuint textureHandler;
};


#endif //TUTORIAL_RANDOMTEXTURE_H
