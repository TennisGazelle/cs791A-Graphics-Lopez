//
// Created by Daniel Lopez on 10/26/17.
//

#ifndef TUTORIAL_SKYBOX_H
#define TUTORIAL_SKYBOX_H

#include <shaders/skyboxShader.h>
#include "camera.h"
#include "cubeMapTexture.h"
#include "object.h"

using namespace std;

class Skybox {
public:
    Skybox(const Camera* pCamera);

    bool Init(const string& dir,
              const string& posX, const string& negX,
              const string& posY, const string& negY,
              const string& posZ, const string& negZ);

    void Render();
private:
    const Camera *camera;
    CubeMapTexture *cubeMapTexture;
    SkyboxShader *shader;
    Object *sphere;

};


#endif //TUTORIAL_SKYBOX_H
