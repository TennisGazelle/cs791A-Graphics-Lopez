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
  if (!m_shadowMap->Init(width, height)) {
    printf("Shadow Map FBO failed to init\n");
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
  if (!m_cube->Init("../meshes/Torus Knot.obj")) {
    printf("Object failed to init\n");
    return false;
  }

  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize()) {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->LoadShader(GL_VERTEX_SHADER, "../shaders/simple_lighting_vertex.glsl")) {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->LoadShader(GL_FRAGMENT_SHADER, "../shaders/simple_lighting_fragment.glsl")) {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize()) {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) {
    printf("m_modelMatrix not found\n");
    return false;
  }

  // Locate the MV matrix
  m_mvMatrix = m_shader->GetUniformLocation("mvMatrix");
  if (m_mvMatrix == INVALID_UNIFORM_LOCATION) {
    printf("m_mvMatrix not found\n");
    return false;
  }

  // Locate the MVP matrix
  m_mvpMatrix = m_shader->GetUniformLocation("mvpMatrix");
  if (m_mvpMatrix == INVALID_UNIFORM_LOCATION) {
    printf("m_mvpMatrix not found\n");
    return false;
  }

  // Locate the light information
  m_spotlight.position = glm::vec4(glm::vec3(5), 1);
  m_spotlight.diffuse = glm::vec4(1, 1, 1, 0);
  m_light = m_shader->GetUniformLocation("light");
  if (m_light == INVALID_UNIFORM_LOCATION) {
    printf("m_light not found\n");
    return false;
  }


  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Keyboard(SDL_Keycode keycode, bool shiftKeyPressed, bool ctrlKeyPressed) {
  switch(keycode) {
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
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // send in the light information to the shader
  glUniform4fv(m_light, 1, glm::value_ptr(m_spotlight.position));

  // Send in the projection aned view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

  // Render the object
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));

  glm::mat4 matrix = m_camera->GetView() * m_cube->GetModel();
  glUniformMatrix4fv(m_mvMatrix, 1, GL_FALSE, glm::value_ptr(matrix));

  matrix = m_camera->GetProjection() * matrix;
  glUniformMatrix4fv(m_mvpMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
  m_cube->Render();

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR ) {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

std::string Graphics::ErrorString(GLenum error) {
  if(error == GL_INVALID_ENUM) {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE) {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION) {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION) {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY) {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else {
    return "None";
  }
}
