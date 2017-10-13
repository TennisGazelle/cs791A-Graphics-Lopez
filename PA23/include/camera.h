#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

static const double DEFAULT_TRANSLATION_DISTANCE = 0.5;

class Camera {
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    void resetValues();
    glm::mat4 GetProjection() const;
    glm::mat4 GetView() const;
    glm::vec3 GetGlobalPosition() const;

    void moveForward_relative(double distance = DEFAULT_TRANSLATION_DISTANCE);
    void moveLeft_relative(double distance = DEFAULT_TRANSLATION_DISTANCE);
    void moveRight_relative(double distance = DEFAULT_TRANSLATION_DISTANCE);
    void moveBackward_relative(double distance = DEFAULT_TRANSLATION_DISTANCE);
    
    void tiltDownward();
    void tiltUpward();

    void pivotLeft_aroundFocus(double distance = DEFAULT_TRANSLATION_DISTANCE);
    void pivotRight_aroundFocus(double distance = DEFAULT_TRANSLATION_DISTANCE);

  private:
    glm::mat4 projection;
    glm::mat4 view;

    glm::vec3 position;
    glm::vec3 focus;

    int m_width;
    int m_height;
};

#endif /* CAMERA_H */
