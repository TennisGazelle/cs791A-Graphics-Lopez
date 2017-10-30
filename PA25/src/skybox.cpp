//
// Created by Daniel Lopez on 10/26/17.
//

#include "skybox.h"

Skybox::Skybox(const Camera *pCamera) : camera(pCamera) {

}

bool Skybox::Init(const string &dir,
                  const string &posX, const string &negX,
                  const string &posY, const string &negY,
                  const string &posZ, const string &negZ) {
    cubeMapTexture = new CubeMapTexture(dir, posX, negX, posY, negY, posZ, negZ);
    if (!cubeMapTexture->Load()) {
        printf("cube mapping texture loading failed\n");
        return false;
    }

    // set up the shader correctly
    shader = new SkyboxShader();
    if (!shader->Initialize()) {
        printf("shader failed to init\n");
        return false;
    }
    if (!shader->LoadShader(GL_VERTEX_SHADER, "../shaders/skybox_vertex.glsl")) {
        printf("Vertex Shader failed to Initialize\n");
        return false;
    }
    if (!shader->LoadShader(GL_FRAGMENT_SHADER, "../shaders/skybox_fragment.glsl")) {
        printf("Fragment Shader failed to Initialize\n");
        return false;
    }
    if (!shader->Finalize()) {
        printf("Program to Finalize\n");
        return false;
    }
    if (!shader->LinkShaderProps()) {
        printf("Lighting shader didn't find some shaders\n");
        return false;
    }

    sphere = new Object();
    if (!sphere->Init("../meshes/planet.obj")) {
        printf("object for skybox failed to init\n");
        return false;
    }
    sphere->setModel(glm::scale(glm::vec3(20, 20, 20)));

    return true;
}

void Skybox::ResetLocation() {
    glm::mat4 matrix = sphere->GetModel();
    matrix[3] = glm::vec4(camera->GetPositionOfCamera(), matrix[3][3]);
    sphere->setModel(matrix);
}

void Skybox::Render() {
    shader->Enable();

    // save the old functions
    GLint oldCullFaceMode, oldDepthFuncMode;
    glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
    glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);

    ResetLocation();

    // grab a big scale transformation
    glm::mat4 matrix = camera->GetProjection() * camera->GetView() * sphere->GetModel();
    glUniformMatrix4fv(shader->mvpMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    cubeMapTexture->Bind(GL_TEXTURE0);
    sphere->Render();

    // replace the old functions
    glCullFace((GLenum)oldCullFaceMode);
    glDepthFunc((GLenum)oldDepthFuncMode);
}