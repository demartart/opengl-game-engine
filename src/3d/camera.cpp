#include "camera.hpp"

#include <glm/glm.hpp>

constexpr float DefaultYaw = -90.0f;
constexpr float DefaultPitch = 0.0f;
constexpr float DefaultSensitivity = 0.1f;
constexpr float DefaultMovementSpeed = 2.5f;

Camera Camera::Create(const glm::vec3 &initPos, const glm::vec3 &up) {
    Camera cam = Camera {
        .position = initPos,
        .globalUp = up,
        .yaw = DefaultYaw,
        .pitch = DefaultPitch,
        .movementSpeed = DefaultMovementSpeed,
        .sensitivity = DefaultSensitivity,
    };
    cam.UpdateVectors();
    return cam;
}

const glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(position, position + forward, up);
}

void Camera::ProcessInput(const glm::vec2 &normalizedMoveDirection, const float deltaTime) {
    float appliedSpeed = movementSpeed * deltaTime;
    position += normalizedMoveDirection.x * right * appliedSpeed;
    position += normalizedMoveDirection.y * forward * appliedSpeed;
}

void Camera::ProcessMouse(const glm::vec2 &mouseDelta, const bool constrainPitch) {
    yaw += mouseDelta.x * sensitivity;
    pitch += mouseDelta.y * sensitivity;
    
    if (constrainPitch && pitch > 89.0f) {
        pitch = 89.0f;
    } 
    
    if (constrainPitch && pitch < -89.0f) {
        pitch = -89.0f;
    }
    
    yaw = glm::mod(yaw, 360.0f);
    UpdateVectors();
}

void Camera::UpdateVectors() {
    glm::vec3 nextForward = glm::vec3 {
        cosf(glm::radians(yaw)) * cosf(glm::radians(pitch)),
        sinf(glm::radians(pitch)),
        sinf(glm::radians(yaw)) * cosf(glm::radians(pitch)) 
    };
    forward = glm::normalize(nextForward);
    right = glm::normalize(glm::cross(forward, globalUp));
    up = glm::normalize(glm::cross(right, forward));
}