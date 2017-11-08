#ifndef __LIGHTING_SHADER_H_
#define __LIGHTING_SHADER_H_

#include "shader.h"

class LightingShader : public Shader {
public:
    bool LinkShaderProps();
    bool FullInitAndLink();

    static const unsigned int MAX_POINT_LIGHTS = 2;
    static const unsigned int MAX_SPOT_LIGHTS = 2;

    GLint projectionMatrix;
    GLint viewMatrix;
    GLint modelMatrix;
    GLint mvMatrix;
    GLint mvpMatrix;
    GLint lightViewMatrix;
    GLint gSampler;
    GLint gShadowMap;
    GLint gNormalMap;
    GLint light;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Direction;
    } m_dirLightLocation;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_pointLightsLocation[MAX_POINT_LIGHTS];

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        GLuint Direction;
        GLuint Cutoff;
        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_spotLightsLocation[MAX_SPOT_LIGHTS];
};

#endif