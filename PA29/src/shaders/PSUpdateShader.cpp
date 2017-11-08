//
// Created by Daniel Lopez on 11/5/17.
//

#include "shaders/PSUpdateShader.h"

PSUpdateShader::PSUpdateShader() {

}

bool PSUpdateShader::FullInitAndLink() {
    if (!Shader::Initialize()) {
        printf("error in ps shader init\n");
        return false;
    }

    if (!LoadShader(GL_VERTEX_SHADER, "../shaders/particle_shaders/ps_update_vs.glsl") ||
        !LoadShader(GL_GEOMETRY_SHADER, "../shaders/particle_shaders/ps_update_gs.glsl") ||
        !LoadShader(GL_FRAGMENT_SHADER, "../shaders/particle_shaders/ps_update_fs.glsl")) {
        printf("particle shader failed to load some of the shaders\n");
        return false;
    }

    if (!Shader::Finalize()) {
        printf("error in ps shader finalizing\n");
        return false;
    }

    cout << "before everything else" << endl;

    // set the 'varying' variables in the geometry shaders
    std::vector<const GLchar*> Varyings(4);
    Varyings[0] = "Type1";
    Varyings[1] = "Position1";
    Varyings[2] = "Velocity1";
    Varyings[3] = "Age1";


    glTransformFeedbackVaryings(m_shaderProg, 4, &Varyings[0], GL_INTERLEAVED_ATTRIBS);

    if (!LinkShaderProps()) {
        printf("error in ps linking shaders props\n");
        return false;
    }

    return true;
}

bool PSUpdateShader::LinkShaderProps() {
    deltaTimeMillis = GetUniformLocation("gDeltaTime");
    if (deltaTimeMillis == INVALID_UNIFORM_LOCATION) {
        printf("gDeltaTime not found\n");
        return false;
    }

    randomTexture = GetUniformLocation("gRandomTexture");
    if (randomTexture == INVALID_UNIFORM_LOCATION) {
        printf("gRandomTexture not found\n");
        return false;
    }

    time = GetUniformLocation("gTime");
    if (time == INVALID_UNIFORM_LOCATION) {
        printf("gTime not found\n");
        return false;
    }

    launcherLifetime = GetUniformLocation("gLauncherLifetime");
    if (launcherLifetime == INVALID_UNIFORM_LOCATION) {
        printf("gLauncherLifetime not found\n");
        return false;
    }

    shellLifetime = GetUniformLocation("gShellLifetime");
    if (shellLifetime == INVALID_UNIFORM_LOCATION) {
        printf("gShellLifetime not found\n");
        return false;
    }

    secondaryShellLifetime = GetUniformLocation("gSecondaryShellLifetime");
    if (secondaryShellLifetime == INVALID_UNIFORM_LOCATION) {
        printf("gSecondaryShellLifetime not found\n");
        return false;
    }

    return true;
}