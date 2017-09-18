#ifndef __SHADOW_MAP_H_
#define __SHADOW_MAP_H_

#include "graphics_headers.h"

class ShadowMap {
public:
    ShadowMap();
    ~ShadowMap();

    bool Init(unsigned int w, unsigned int h);
    void bindForWriting();
    void bindForReading(GLenum textureUnit);

private:
    GLuint m_fbo;
    GLuint m_shadowMap;
}

#endif // __SHADOW_MAP_H_