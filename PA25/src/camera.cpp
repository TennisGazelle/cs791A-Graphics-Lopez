#include "camera.h"

Camera::Camera() {
  position = glm::vec3(0.0, 8.0, 16.0);
  focus = glm::vec3(0.0);
}

Camera::~Camera() {

}

bool Camera::Initialize(int w, int h) {
  m_width = w;
  m_height = h;
  resetValues();
  return true;
}

void Camera::resetValues() {
  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic
  //  for this project having them static will be fine
  view = glm::lookAt( position, //Eye Position
                      focus, //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(m_width)/float(m_height), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 100.0f); //Distance to the far plane,
}

glm::mat4 Camera::GetProjection() const {
  return projection;
}

glm::mat4 Camera::GetView() const {
  return view;
}

void Camera::moveForward_relative(double distance) {
  glm::vec3 direction = float(distance) * glm::normalize(focus - position);
  position += direction;
  focus += direction;
  resetValues();
}

void Camera::moveBackward_relative(double distance) {
  glm::vec3 direction = float(distance) * glm::normalize(focus - position);
  position -= direction;
  focus -= direction;
  resetValues();
}

void Camera::moveLeft_relative(double distance) {
  glm::vec3 cameraDirection = focus - position;
  cameraDirection.y = 0;
  glm::vec3 direction = float(distance) * glm::normalize(
    glm::cross(glm::vec3(0.0, 1.0, 0.0), cameraDirection)
  );
  position += direction;
  focus += direction;
  resetValues();
}

void Camera::moveRight_relative(double distance) {
  glm::vec3 cameraDirection = focus - position;
  cameraDirection.y = 0;
  glm::vec3 direction = float(distance) * glm::normalize(
    glm::cross(glm::vec3(0.0, 1.0, 0.0), cameraDirection)
  );
  position -= direction;
  focus -= direction;
  resetValues();
}

void Camera::pivotLeft_aroundFocus(double distance) {
  glm::vec3 direction = float(distance) * glm::normalize(
    glm::cross(glm::vec3(0.0, 1.0, 0.0), focus - position)
  );
  position += direction;
  resetValues();
}

void Camera::pivotRight_aroundFocus(double distance) {
  glm::vec3 direction = float(distance) * glm::normalize(
    glm::cross(glm::vec3(0.0, 1.0, 0.0), focus - position)
  );
  position -= direction;
  resetValues();
}