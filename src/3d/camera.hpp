#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 up, right, forward, globalUp;
    float yaw, pitch;

    float movementSpeed;
    float sensitivity;
    
    static Camera Create(const glm::vec3 &initPos = { 0.0f, 0.0f, 0.0f }, const glm::vec3 &up = { 0.0f, 1.0f, 0.0f });
    
    const glm::mat4 GetViewMatrix() const;
    
    void ProcessInput(const glm::vec2 &normalizedMoveDirection, const float deltaTime);
    void ProcessMouse(const glm::vec2 &mouseDelta, const bool constrainPitch = true);
    
    void UpdateVectors();
};

#endif