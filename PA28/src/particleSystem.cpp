//
// Created by Daniel Lopez on 11/3/17.
//

#include <Particle.h>
#include <textureManager.h>
#include "particleSystem.h"

ParticleSystem::ParticleSystem() : currentVB(0), currentTFB(0) {

}

ParticleSystem::~ParticleSystem() {

}

bool ParticleSystem::Init(const glm::vec3 &position) {
    vector<Particle> particles(MAX_PARTICLES);

    particles[0].type = PARTICLE_TYPE_LAUNCHER;
    particles[0].position = position;
    particles[0].velocity = glm::vec3(0, 0.001f, 0);
    particles[0].lifetimeMillis = 0.0f;

    glGenTransformFeedbacks(2, &transformFeedback[0]);
    glGenBuffers(2, &particleBuffer[0]);

    for (unsigned int i = 0; i < 2; i++) {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedback[i]);
        glBindBuffer(GL_ARRAY_BUFFER, particleBuffer[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Particle), &particles[0], GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, particleBuffer[i]);
    }

    //
    // SHADER
    //
    psuShader = new PSUpdateShader();
    if (!psuShader->FullInitAndLink()) {
        printf("error in psy shader init\n");
        return false;
    }
    cout << "after binding" << endl;
    psuShader->Enable();

    // set random texture unit
    glUniform1i(psuShader->randomTexture, RANDOM_TEXTURE_UNIT_INDEX);
    // set launcher lifetime
    glUniform1f(psuShader->launcherLifetime, 100.0f);
    // set shell lifetime
    glUniform1f(psuShader->shellLifetime, 10000.0f);
    // set secondary shell lifetime
    glUniform1f(psuShader->secondaryShellLifetime, 2500.0f);

    cout << "after shader" << endl;

    //
    // RANDOM TEXTURE
    //
    if (!randomTexture.Init(1000)) {
        printf("error in psu random texture init\n");
        return false;
    }
    randomTexture.Bind(RANDOM_TEXTURE_UNIT);

    cout << "after random texture" << endl;

    //
    // BILLBOARD
    //
    bbShader = new BillboardShader();
    if (!bbShader->FullInitAndLink()) {
        printf("billboard shader in particle system error\n");
        return false;
    }
    bbShader->Enable();
    // set color texture unit index
    glUniform1i(bbShader->colorMap, COLOR_TEXTURE_UNIT_INDEX);
    // set billboard size
    glUniform1f(bbShader->size, 0.1f);

    cout << "after billboard" << endl;

    //
    // TEXTURE
    //
    if (!TMInstance->addTexture("red_dot", "../textures/fireworks_red.jpg")) {
        printf("ps texture couldn't load\n");
        return false;
    }
    particleTexture = TMInstance->getTexture("red_dot");

    return true;
}

void ParticleSystem::Render(unsigned int deltaTimeMillis, const glm::mat4 &viewPosition, const glm::vec3 &cameraPos) {
    time += deltaTimeMillis;

    UpdateParticles(deltaTimeMillis);
    RenderParticles(viewPosition, cameraPos);

    currentVB = currentTFB;
    currentTFB = (currentTFB + 1) & 0x1; // toggle between the two buffers...
}

void ParticleSystem::UpdateParticles(unsigned int deltaTimeMillis) {
    psuShader->Enable();
    // set time
    glUniform1f(psuShader->time, time);
    // set delta time
    glUniform1f(psuShader->deltaTimeMillis, deltaTimeMillis);

    randomTexture.Bind(RANDOM_TEXTURE_UNIT);

    glEnable(GL_RASTERIZER_DISCARD);

    glBindBuffer(GL_ARRAY_BUFFER, particleBuffer[currentVB]);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedback[currentTFB]);

    // SIMILAR TO VERTEX ARRAY ASSIGNING IN OBJECT
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *) offsetof(Particle, type));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *) offsetof(Particle, position));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *) offsetof(Particle, velocity));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *) offsetof(Particle, lifetimeMillis));
    glBeginTransformFeedback(GL_POINTS);
    if (isFirst) {
        glDrawArrays(GL_POINTS, 0, 1);
        isFirst = false;
    } else {
        glDrawTransformFeedback(GL_POINTS, transformFeedback[currentVB]);
//        isFirst = true;
    }
    glEndTransformFeedback();
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}

void ParticleSystem::RenderParticles(const glm::mat4 &viewPosition, const glm::vec3 &cameraPosition) {
    bbShader->Enable();
    // set the camera
    glUniform3fv(bbShader->cameraPosition, 1, glm::value_ptr(cameraPosition));
    // set the VP
    glUniformMatrix4fv(bbShader->vpMatrix, 1, GL_FALSE, glm::value_ptr(viewPosition));

    particleTexture->enable(COLOR_TEXTURE_UNIT);

    glDisable(GL_RASTERIZER_DISCARD);

    glBindBuffer(GL_ARRAY_BUFFER, particleBuffer[currentTFB]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *) offsetof(Particle, position));
    glDrawTransformFeedback(GL_POINTS, transformFeedback[currentTFB]);
    glDisableVertexAttribArray(0);
}