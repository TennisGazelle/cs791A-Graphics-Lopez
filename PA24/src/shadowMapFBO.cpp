#ifndef __SHADOW_MAP_FBO_CPP_
#define __SHADOW_MAP_FBO_CPP_
//
// Created by Daniel Lopez on 10/17/17.
//

#include "shadowMapFBO.h"

ShadowMapFBO::ShadowMapFBO() {

}

bool ShadowMapFBO::Init(int width, int height) {
    // create the FBO
    glGenFramebuffers(1, &fbo);

    // create depth buffer image
    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    // note we're using GL_DEPTH_COMPONENT instead of GL_RGB for the same idea of a buffer
    // last parameter of glTexImage2d is null (not supplying any data by which to init the buffer)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    // if texture range goes out of frame, clamp, between 0 and 1 (may happen when projection window contains stuff outside the light's POV)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // need to attach frame buffer to the fbo (sets the fbo as "current" fbo to future ops to be done on it)
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // attachd shadow mpa teture to the depth attachment point of the FBO (last param is for mipmap resolution, which is set to highest)
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

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

void ShadowMapFBO::BindForReading(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
}

void ShadowMapFBO::BindForWriting() const {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

#endif