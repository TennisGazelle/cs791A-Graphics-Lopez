//
// Created by Daniel Lopez on 10/17/17.
//

#ifndef __SHADOW_MAP_FBO_H_
#define __SHADOW_MAP_FBO_H_

#include "graphics_headers.h"

class ShadowMapFBO {
public:
    ShadowMapFBO();
    bool Init(int width, int height);
    void BindForReading(GLenum textureUnit) const;
    void BindForWriting() const;

    GLuint fbo;
    GLuint shadowMap;
};


#endif //__SHADOW_MAP_FBO_H_
