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

  // init shadow mapping
  m_shadowMap = new ShadowMap();
  if (!m_shadowMap->Init(1300, 1300)) {
    printf("Shadow Map FBO failed to init\n");
    return false;
  }

  // init the lighting
  m_lighting = new Lighting();
  if (!m_lighting->Init()) {
    printf("Lighting technique failed to init\n");
    return false;
  }

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height)) {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Create the object
  m_cube = new Object();
  m_floor = new Object();
  if (!m_cube->Init("../meshes/Torus Knot.obj")) {
    printf("Object failed to init\n");
    return false;
  }
  if (!m_floor->Init("../meshes/plane.obj")) {
    printf("floor failed to init\n");
    return false;
  }
  m_floor->model = glm::scale(glm::mat4(1.0), glm::vec3(5.0));

  // Locate the light information
  m_spotlight.position = glm::vec4(glm::vec3(10), 0);
  m_spotlight.diffuse = glm::vec4(1, 1, 1, 0);

  // Set up the shaders
  m_shadowMapShader = new Shader();
  m_lightingShader = new Shader();
  if (!m_shadowMapShader->Initialize() || !m_lightingShader->Initialize()) {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if (!m_shadowMapShader->LoadShader(GL_VERTEX_SHADER, "../shaders/shadow_map_vertex.glsl")) {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }
  if (!m_lightingShader->LoadShader(GL_VERTEX_SHADER, "../shaders/lighting_vertex.glsl")) {
    printf("Vertex lighting shader failed to Initialize\n");
    return false;
  }
  // Add the fragment shader
  if (!m_shadowMapShader->LoadShader(GL_FRAGMENT_SHADER, "../shaders/shadow_map_fragment.glsl")) {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }
  if (!m_lightingShader->LoadShader(GL_FRAGMENT_SHADER, "../shaders/lighting_fragment.glsl")) {
    printf("Fragment lighting shader failed to init\n");
    return false;
  }

  // Connect the program
  if (!m_shadowMapShader->Finalize()) {
    printf("shadow map shader to finalize");
    return false;
  }
  if (!m_lightingShader->Finalize()) {
    printf("lighing shader to finalize\n");
    return false;
  }

  // Linking all the objects in the shaders
  if (!ShaderLinking()) {
    printf("Error in linking the objects to the shaders\n");
    return false;
  }

  // enabled the shader
  m_shadowMapShader->Enable();
  m_lightingShader->Enable();

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

bool Graphics::ShaderLinking() {

  // Locate the projection matrix in the shader
  m_shadowMapShaderInfo.m_projectionMatrix = m_shadowMapShader->GetUniformLocation("projectionMatrix");
  if (m_shadowMapShaderInfo.m_projectionMatrix == INVALID_UNIFORM_LOCATION) {
    printf("m_shadowMapShaderInfo.m_projectionMatrix not found\n");
    return false;
  }
  // Locate the view matrix in the shader
  m_shadowMapShaderInfo.m_viewMatrix = m_shadowMapShader->GetUniformLocation("viewMatrix");
  if (m_shadowMapShaderInfo.m_viewMatrix == INVALID_UNIFORM_LOCATION) {
    printf("m_viewMatrix not found\n");
    return false;
  }
  // Locate the model matrix in the shader
  m_shadowMapShaderInfo.m_modelMatrix = m_shadowMapShader->GetUniformLocation("modelMatrix");
  if (m_shadowMapShaderInfo.m_modelMatrix == INVALID_UNIFORM_LOCATION) {
    printf("m_modelMatrix not found\n");
    return false;
  }
  // Locate the MV matrix
  m_shadowMapShaderInfo.m_mvMatrix = m_shadowMapShader->GetUniformLocation("mvMatrix");
  if (m_shadowMapShaderInfo.m_mvMatrix == INVALID_UNIFORM_LOCATION) {
    printf("m_mvMatrix not found\n");
    return false;
  }
  // Locate the MVP matrix
  m_shadowMapShaderInfo.m_mvpMatrix = m_shadowMapShader->GetUniformLocation("mvpMatrix");
  if (m_shadowMapShaderInfo.m_mvpMatrix == INVALID_UNIFORM_LOCATION) {
    printf("m_mvpMatrix not found\n");
    return false;
  }

  m_shadowMapShaderInfo.m_light = m_shadowMapShader->GetUniformLocation("light");
  if (m_shadowMapShaderInfo.m_light == INVALID_UNIFORM_LOCATION) {
    printf("m_light not found\n");
    return false;
  }
  m_shadowMapShaderInfo.m_gShadowMap = m_shadowMapShader->GetUniformLocation("gShadowMap");
  if (m_shadowMapShaderInfo.m_gShadowMap == INVALID_UNIFORM_LOCATION) {
    printf("shadow map not found\n");
    return false;
  }

  // Now for the lighting Uniform locations
  m_lightingShaderInfo.m_mvpMatrix = m_lightingShader->GetUniformLocation("gMVP");
  m_lightingShaderInfo.m_lightMVPMatrix = m_lightingShader->GetUniformLocation("gLightMVP");
  m_lightingShaderInfo.m_modelMatrix = m_lightingShader->GetUniformLocation("gModel");
  m_lightingShaderInfo.m_sampler = m_lightingShader->GetUniformLocation("gSampler");
  m_lightingShaderInfo.m_gShadowMap = m_lightingShader->GetUniformLocation("gShadowMap");
  m_lightingShaderInfo.m_eyeWorldPos = m_lightingShader->GetUniformLocation("gEyeWorldPos");
  m_lightingShaderInfo.m_pointLight_color = m_lightingShader->GetUniformLocation("pointLight.base.color");
  m_lightingShaderInfo.m_pointLight_ambientIntensity = m_lightingShader->GetUniformLocation("pointLight.base.ambientIntensity");
  m_lightingShaderInfo.m_pointLight_diffuseIntensity = m_lightingShader->GetUniformLocation("pointLight.base.diffuseIntensity");
    m_lightingShaderInfo.m_pointLight_position = m_lightingShader->GetUniformLocation("pointLight.position");

  if (m_lightingShaderInfo.m_mvpMatrix == INVALID_UNIFORM_LOCATION ||
          m_lightingShaderInfo.m_lightMVPMatrix == INVALID_UNIFORM_LOCATION ||
          m_lightingShaderInfo.m_modelMatrix == INVALID_UNIFORM_LOCATION ||
          m_lightingShaderInfo.m_sampler == INVALID_UNIFORM_LOCATION ||
          m_lightingShaderInfo.m_gShadowMap == INVALID_UNIFORM_LOCATION ||
          m_lightingShaderInfo.m_eyeWorldPos == INVALID_UNIFORM_LOCATION) {
    return false;
  }

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
            shiftKeyPressed ? m_camera->pivotLeft_aroundFocus() : m_camera->moveLeft_relative();
            break;
        case SDLK_RIGHT:
            shiftKeyPressed ? m_camera->pivotRight_aroundFocus() : m_camera->moveRight_relative();
        default:
            break;
    }
}

void Graphics::Update(unsigned int dt) {
    // Update the object
    m_cube->Update(dt);
}

void Graphics::Render() {
    ShadowMapPass();
    RenderPass();
}

void Graphics::ShadowMapPass() {
  m_shadowMapShader->Enable();
  m_shadowMap->bindForWriting();

  glClear(GL_DEPTH_BUFFER_BIT);

  // send in the light information to the shader
  glUniform4fv(m_shadowMapShaderInfo.m_light, 1, glm::value_ptr(m_spotlight.position));
  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_shadowMapShaderInfo.m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));

  glm::mat4 viewFromLight = glm::lookAt(glm::vec3(m_spotlight.position), m_spotlight.direction, glm::vec3(0.0, 1.0, 0.0));
  glUniformMatrix4fv(m_shadowMapShaderInfo.m_viewMatrix, 1, GL_FALSE, glm::value_ptr(viewFromLight));

  // pass in the cube
  glUniformMatrix4fv(m_shadowMapShaderInfo.m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));

  glm::mat4 matrix = viewFromLight * m_cube->GetModel();
  glUniformMatrix4fv(m_shadowMapShaderInfo.m_mvMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
  matrix = m_camera->GetProjection() * matrix;
  glUniformMatrix4fv(m_shadowMapShaderInfo.m_mvpMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
  m_cube->Render();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  auto error = glGetError();
  if ( error != GL_NO_ERROR ) {
    string val = ErrorString( error );
    std::cout<< "[Shadow Pass] - Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

void Graphics::RenderPass() {
  //clear the screen
  glClearColor(0.0, 0.0, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_lightingShader->Enable();

  // set the texture unit
  glUniform1i(m_shadowMapShaderInfo.m_gShadowMap, 0);
  // bind the shadow map
  m_shadowMap->bindForReading(GL_TEXTURE0);

  // send in the light information to the shader
    glUniform3fv(m_lightingShaderInfo.m_eyeWorldPos, 1, glm::value_ptr(m_camera->GetGlobalPosition()));
    glUniform3fv(m_lightingShaderInfo.m_pointLight_position, 1, glm::value_ptr(m_spotlight.position));

  // Render the object
    glm::mat4 matrix = glm::lookAt(glm::vec3(m_spotlight.position), glm::vec3(m_spotlight.direction), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(m_lightingShaderInfo.m_lightMVPMatrix, 1, GL_FALSE, glm::value_ptr(matrix));


  matrix = m_camera->GetProjection() * m_camera->GetView() * m_floor->GetModel();
  glUniformMatrix4fv(m_lightingShaderInfo.m_mvpMatrix, 1, GL_FALSE, glm::value_ptr(matrix));

  m_floor->Render();

    // render the floor
  glUniformMatrix4fv(m_lightingShaderInfo.m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
  matrix = m_camera->GetView() * m_cube->GetModel();
  glUniformMatrix4fv(m_lightingShaderInfo.m_mvMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
  matrix = m_camera->GetProjection() * matrix;
  glUniformMatrix4fv(m_lightingShaderInfo.m_mvpMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
  m_cube->Render();

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR ) {
    string val = ErrorString( error );
    std::cout<< "[Render Pass] - Error initializing OpenGL! " << error << ", " << val << std::endl;
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
