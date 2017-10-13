#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SDL2/SDL.h>

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "shadow_map.h"
#include "lighting.h"

using namespace std;

class Graphics {
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    bool ShaderLinking();
    void Update(unsigned int dt);
    void Render();
    void ShadowMapPass();
    void RenderPass();
    void Keyboard(SDL_Keycode keycode, bool shiftKeyPressed, bool ctrlKeyPressed);

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;

    struct ShaderLocInfo{
      GLint m_projectionMatrix;
      GLint m_viewMatrix;
      GLint m_modelMatrix;
      GLint m_mvMatrix;
      GLint m_mvpMatrix;
      GLint m_light;
      GLint m_gShadowMap;
    };
    struct ShadowMapShaderLocInfo : ShaderLocInfo {};
    struct LightingShaderLocInfo : ShaderLocInfo {
        GLint m_lightMVPMatrix; // gLightMVP
        GLint m_sampler;        // gSampler
        GLint m_eyeWorldPos;    // gEyeWorldPos
        GLint m_pointLight_color;
        GLint m_pointLight_ambientIntensity;
        GLint m_pointLight_diffuseIntensity;
        GLint m_pointLight_position;
    };

    // shadow map information and shading
    Shader *m_shadowMapShader;
    ShadowMap *m_shadowMap;
    ShadowMapShaderLocInfo m_shadowMapShaderInfo;

    // lighting information and shading
    Shader *m_lightingShader;
    Lighting *m_lighting;
    LightingShaderLocInfo m_lightingShaderInfo;

    Light m_spotlight;

    Object *m_cube;
    Object *m_floor;
};

#endif /* GRAPHICS_H */
