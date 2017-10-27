#include <shadowMapFBO.h>
#include "graphics.h"

Graphics::Graphics() {

}

Graphics::~Graphics() {

}

bool Graphics::Initialize(int width, int height) {
    // Used for the linux OS
#if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK) {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
#endif

    // For OpenGL 3
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Init Camera
    m_camera = new Camera();
    if (!m_camera->Initialize(width, height)) {
        printf("Camera Failed to Initialize\n");
        return false;
    }

    // Create the object
    m_cube = new Object();
    m_floor = new Object();
    if (!m_cube->Init("../meshes/Torus Knot.obj", "../textures/chrome_mercury.jpg")) {
        printf("Object failed to init\n");
        return false;
    }
    if (!m_floor->Init("../meshes/plane.obj", "../textures/stone_floor.jpg")) {
        printf("floor failed to init\n");
        return false;
    }
    m_cube->setModel(glm::translate(glm::vec3(0, 2.5f, 0)));

    // Set up the shaders
    m_shader = new LightingShader();
    if (!m_shader->Initialize()) {
        printf("Shader Failed to Initialize\n");
        return false;
    }
    // Add the vertex shader
    if (!m_shader->LoadShader(GL_VERTEX_SHADER, "../shaders/simple_lighting_vertex.glsl")) {
        printf("Vertex Shader failed to Initialize\n");
        return false;
    }
    // Add the fragment shader
    if (!m_shader->LoadShader(GL_FRAGMENT_SHADER, "../shaders/simple_lighting_fragment.glsl")) {
        printf("Fragment Shader failed to Initialize\n");
        return false;
    }
    // Connect the program
    if (!m_shader->Finalize()) {
        printf("Program to Finalize\n");
        return false;
    }
    if (!m_shader->LinkShaderProps()) {
        printf("Lighting shader didn't find some shaders\n");
        return false;
    }

    // DEBUGGING
    // declare that skybox object and init it
    skybox = new Skybox(m_camera);
    if (!skybox->Init("../textures/SkyboxSet1/CloudyLightRays/",
                      "CLRRight.png", "CLRLeft.png",
                      "CLRUp.png", "CLRDown.png",
                      "CLRFront.png", "CLRBack.png")) {
        printf("skybox object failed to init in graphics object\n");
        return false;
    }

//    m_shadowMapShader = new ShadowMapShader();
//    if (!m_shadowMapShader->Initialize()) {
//        printf("shadow map shader failed to init\n");
//        return false;
//    }
//    if (!m_shadowMapShader->LoadShader(GL_VERTEX_SHADER, "../shaders/shadow_map_vertex.glsl")) {
//        printf("shadow map vertex failed to init\n");
//        return false;
//    }
//    if (!m_shadowMapShader->LoadShader(GL_FRAGMENT_SHADER, "../shaders/shadow_map_fragment.glsl")) {
//        printf("shadow map vertex shader failed to init\n");
//        return false;
//    }
//    if (!m_shadowMapShader->Finalize()) {
//        printf("shader failed to finalize\n");
//        return false;
//    }
//    if (!m_shadowMapShader->LinkShaderProps()) {
//        printf("Shadow shader didn't find some variables\n");
//        return false;
//    }
//
//    // create the frame buffer
//    m_shadowMapFBO = new ShadowMapFBO();
//    if (!m_shadowMapFBO->Init(width, height)) {
//        printf("error with init fbo\n");
//        return false;
//    }

    // Locate the light information
    m_spotlight.position = glm::vec4(5, 2, 0, 1);
    m_spotlight.diffuse = glm::vec4(1, 1, 1, 0);
    m_spotlight.direction = glm::normalize(m_spotlight.position);

    //enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return true;
}

void Graphics::Keyboard(SDL_Keycode keycode, bool shiftKeyPressed, bool ctrlKeyPressed) {
    switch (keycode) {
        case SDLK_UP:
            m_camera->moveForward_relative();
            break;

        case SDLK_DOWN:
            m_camera->moveBackward_relative();
            break;

        case SDLK_LEFT:
            if (shiftKeyPressed) {              // SHIFT + left, pivot left
                m_spotlight.position.x += 0.25f;
            } else if (ctrlKeyPressed) {        // CTRL + left, move light left
                m_camera->pivotLeft_aroundFocus();
            } else {                            // left, move left
                m_camera->moveLeft_relative();
            }
            break;

        case SDLK_RIGHT:
            if (shiftKeyPressed) {
                m_spotlight.position.x -= 0.25f;
            } else if (ctrlKeyPressed) {
                m_camera->pivotRight_aroundFocus();
            } else {
                m_camera->moveRight_relative();
            }
            break;

        case SDLK_KP_2:
            m_spotlight.direction.z += 0.25;
            break;
        case SDLK_KP_8:
            m_spotlight.direction.z -= 0.25;
            break;


        default:
            break;
    }
}

void Graphics::Update(unsigned int dt) {
    // Update the object
    m_cube->Update(dt);
    // update the location of the light
    static float angle = 0.01;
    static glm::mat4 rotation = glm::translate(glm::vec3(10, 5, 0));
    rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) *rotation;
    m_spotlight.position = rotation[3];
}

void Graphics::Render() {
//    ShadowRenderPass();
    LightingRenderPass();
    SkyboxRenderPass();
}

void Graphics::SkyboxRenderPass() {
    skybox->Render();
}

void Graphics::ShadowRenderPass() {
    // clear the buffer
    m_shadowMapFBO->BindForWriting();
    glClear(GL_DEPTH_BUFFER_BIT);

    // set it up for writing
    m_shadowMapShader->Enable();

    // make the view from the light
    glm::mat4 viewFromLight = glm::lookAt(glm::vec3(m_spotlight.position), glm::vec3(m_spotlight.direction), glm::vec3(0, 1, 0));

    // send in light
    glUniformMatrix4fv(m_shadowMapShader->projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
    glUniformMatrix4fv(m_shadowMapShader->viewMatrix, 1, GL_FALSE, glm::value_ptr(viewFromLight));
    glUniformMatrix4fv(m_shadowMapShader->modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
    glm::mat4 matrix = viewFromLight * m_cube->GetModel();
    glUniformMatrix4fv(m_shadowMapShader->mvMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    matrix = m_camera->GetProjection() * matrix;
    glUniformMatrix4fv(m_shadowMapShader->mvpMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    m_cube->Render();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Graphics::LightingRenderPass() {
    glm::mat4 matrix;
//    m_shadowMapFBO->BindForReading(GL_TEXTURE1);
    //clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Start the correct program
    m_shader->Enable();

    // set the texture unit
    glUniform1i(m_shader->gSampler, 0);

    // send in the light information to the shader
    glUniform4fv(m_shader->light, 1, glm::value_ptr(m_spotlight.position));
    glm::mat4 viewFromLight = glm::lookAt(glm::vec3(m_spotlight.position), glm::vec3(m_spotlight.direction), glm::vec3(0, 1, 0));

    // Send in the projection aned view to the shader
    glUniformMatrix4fv(m_shader->projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
    glUniformMatrix4fv(m_shader->viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));
    glUniformMatrix4fv(m_shader->lightViewMatrix, 1, GL_FALSE, glm::value_ptr(viewFromLight));

    // Render the cube object
    matrix = m_camera->GetView() * m_cube->GetModel();
    glUniformMatrix4fv(m_shader->modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
    glUniformMatrix4fv(m_shader->mvMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    matrix = m_camera->GetProjection() * matrix;
    glUniformMatrix4fv(m_shader->mvpMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    m_cube->Render();

    // Render the floor object
    matrix = m_camera->GetView() * m_floor->GetModel();
    glUniformMatrix4fv(m_shader->modelMatrix, 1, GL_FALSE, glm::value_ptr(m_floor->GetModel()));
    glUniformMatrix4fv(m_shader->mvMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    matrix = m_camera->GetProjection() * matrix;
    glUniformMatrix4fv(m_shader->mvpMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
    m_floor->Render();

    // Get any errors from OpenGL
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        string val = ErrorString(error);
//        std::cout << "Error initializing OpenGL! " << error << ", " << val << std::endl;
    }
}

std::string Graphics::ErrorString(GLenum error) {
    if (error == GL_INVALID_ENUM) {
        return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
    } else if (error == GL_INVALID_VALUE) {
        return "GL_INVALID_VALUE: A numeric argument is out of range.";
    } else if (error == GL_INVALID_OPERATION) {
        return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
    } else if (error == GL_INVALID_FRAMEBUFFER_OPERATION) {
        return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
    } else if (error == GL_OUT_OF_MEMORY) {
        return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
    } else {
        return "None";
    }
}
