#ifndef __SHADOW_MAP_CPP_
#define __SHADOW_MAP_CPP_

#include "shadow_map.h"

ShadowMap::ShadowMap() {
    m_fbo = 0;
    m_shadowMap = 0;
}

ShadowMap::~ShadowMap() {
    if (m_fbo != 0) {
        glDeleteFramebuffers(1, &m_fbo);
    }
    if (m_shadowMap != 0) {
        glDeleteFramebuffers(1, &m_shadowMap);
    }
}

bool ShadowMap::Init(unsigned int w, unsigned int h) {
    // create the FBO
    glGenFramebuffers(1, &m_fbo);

    // create depth buffer image
    glGenTextures(1, &m_shadowMap);
    glBindTexture(GL_TEXTURE_2D, m_shadowMap);
        // note we're using GL_DEPTH_COMPONENT instead of GL_RGB for the same idea of a buffer
        // last parameter of glTexImage2d is null (not supplying any data by which to init the buffer)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // if texture range goes out of frame, clamp, between 0 and 1 (may happen when projection window contains stuff outside the light's POV)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // need to attach frame buffer to the fbo (sets the fbo as "current" fbo to future ops to be done on it)
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    // attachd shadow mpa teture to the depth attachment point of the FBO (last param is for mipmap resolution, which is set to highest)
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0);

    // disable writes to the color buffer (for now)
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    // init error checking
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FrameBufferObject failed to init\n");
        return false;
    }

    return true;
}

void ShadowMap::bindForReading(GLenum textureUnit) {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_shadowMap);
}

void ShadowMap::bindForWriting() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}

#endif //__SHADOW_MAP_CPP_