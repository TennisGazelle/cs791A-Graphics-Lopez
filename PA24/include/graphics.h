#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "lightingShader.h"
#include "shadowMapShader.h"
#include "object.h"
#include "shadowMapFBO.h"

class Graphics {
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();
    void ShadowRenderPass();
    void LightingRenderPass();
    void Keyboard(SDL_Keycode keycode, bool shiftKeyPressed, bool ctrlKeyPressed);

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    LightingShader *m_shader;
    ShadowMapShader *m_shadowMapShader;
    ShadowMapFBO *m_shadowMapFBO;

    Object *m_cube;
    Object *m_floor;

    Light m_spotlight;
};

#endif /* GRAPHICS_H */
