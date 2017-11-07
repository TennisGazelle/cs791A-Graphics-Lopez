//
// Created by Daniel Lopez on 11/3/17.
//

#ifndef TUTORIAL_PARTICLESYSTEM_H
#define TUTORIAL_PARTICLESYSTEM_H

#include <shaders/billboardShader.h>
#include <shaders/PSUpdateShader.h>
#include "graphics_headers.h"
#include "texture.h"
#include "randomTexture.h"

const static unsigned int MAX_PARTICLES = 100;
const static float PARTICLE_TYPE_LAUNCHER = 1.0;

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();

    bool Init(const glm::vec3& position);

    void Render(unsigned int deltaTimeMillis, const glm::mat4& viewPosition, const glm::vec3& cameraPos);

private:
    void UpdateParticles(unsigned int deltaTimeMillis);
    void RenderParticles(const glm::mat4& viewPosition, const glm::vec3& cameraPosition);

    bool isFirst;
    unsigned int currentVB;
    unsigned int currentTFB;

    GLuint particleBuffer[2];
    GLuint transformFeedback[2];

    BillboardShader *bbShader;
    PSUpdateShader *psuShader;

    RandomTexture randomTexture;
    Texture* particleTexture;
    unsigned int time;
};


#endif //TUTORIAL_PARTICLESYSTEM_H
