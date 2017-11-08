#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shaders/lightingShader.h"
#include "shaders/shadowMapShader.h"
#include "object.h"
#include "shadowMapFBO.h"
#include "cubeMapTexture.h"
#include "skybox.h"
#include "billboardList.h"
#include "particleSystem.h"

class Graphics {
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();
    void ShadowRenderPass();
    void SkyboxRenderPass();
    void LightingRenderPass();
    void GeometryRenderPass();
    void ParticleRenderPass();
    void Keyboard(SDL_Keycode keycode, bool shiftKeyPressed, bool ctrlKeyPressed);

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    LightingShader *m_shader;
    ShadowMapShader *m_shadowMapShader;
    ShadowMapFBO *m_shadowMapFBO;

    Object *m_cube;
    Object *m_floor;
    Object *m_quad;

//    BillboardList m_bblist;
    Skybox *skybox;

    Light m_spotlight;

    // DEBUGGING
    ParticleSystem *particleSystem;

    unsigned int dt;
};

#endif /* GRAPHICS_H */
