#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <SDL2/SDL.h>

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "shadow_map.h"

using namespace std;

class Graphics {
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();
    void ShadowMapPass();
    void RenderPass();
    void Keyboard(SDL_Keycode keycode, bool shiftKeyPressed, bool ctrlKeyPressed);

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;
    ShadowMap *m_shadowMap;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    GLint m_mvMatrix;
    GLint m_mvpMatrix;
    GLint m_light;

    Object *m_cube;

    Light m_spotlight;
};

#endif /* GRAPHICS_H */
