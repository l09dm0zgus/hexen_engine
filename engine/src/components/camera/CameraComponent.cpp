//
// Created by cx9ps3 on 10.01.23.
//

#include "CameraComponent.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include <SDL3/SDL.h>
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

void hexen::engine::components::graphics::CameraComponent::updateViewMatrix()
{

    if(bIsIsometric)
    {
        currentPitchAngle -= static_cast<float>(atan(sin(glm::radians(currentYawAngle))));
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(currentYawAngle)) * cos(glm::radians(currentPitchAngle));
    direction.y = sin(glm::radians(currentPitchAngle));
    direction.z = sin(glm::radians(currentYawAngle)) * cos(glm::radians(currentPitchAngle));

    cameraTarget = glm::normalize(direction);

    cameraRight = glm::normalize(glm::cross(cameraTarget, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraTarget));
    view = glm::lookAt(position, position + cameraTarget, cameraUp);

}

hexen::engine::components::graphics::CameraComponent::CameraComponent(core::i32 viewportWidth, core::i32 viewportHeight,float FOV,bool isIsometric)
{
    this->FOV = FOV;
    updateProjectionMatrix(viewportWidth,viewportHeight);
    updateViewMatrix();
}

glm::mat4 hexen::engine::components::graphics::CameraComponent::getViewMatrix()
{
    return view;
}


glm::mat4 hexen::engine::components::graphics::CameraComponent::getProjectionMatrix()
{
    return projection;
}

void hexen::engine::components::graphics::CameraComponent::start()
{

}


void hexen::engine::components::graphics::CameraComponent::update(float deltaTime)
{
    this->deltaTime = deltaTime;
}

void hexen::engine::components::graphics::CameraComponent::moveForward(float value)
{
    position.z += value * deltaTime;
    updateViewMatrix();
}

void hexen::engine::components::graphics::CameraComponent::moveRight(float value)
{
    position.x += value * deltaTime;
    updateViewMatrix();
}

void hexen::engine::components::graphics::CameraComponent::zoom(float value)
{
    position += glm::normalize(glm::cross(cameraTarget, cameraUp)) * value * deltaTime;
    updateViewMatrix();
}

void hexen::engine::components::graphics::CameraComponent::updateProjectionMatrix(core::u32 newWindowWidth, core::u32 newWindowHeight)
{
    glViewport(0,0,newWindowWidth,newWindowHeight);
    projection = glm::perspective(glm::radians(FOV), static_cast<float>(newWindowWidth) / static_cast<float>(newWindowHeight), 0.1f, 100.0f);
}

void hexen::engine::components::graphics::CameraComponent::yaw(float yawAngle)
{
    currentYawAngle += yawAngle * deltaTime;
    updateViewMatrix();

}

void hexen::engine::components::graphics::CameraComponent::pitch(float pitchAngle)
{
    currentPitchAngle += pitchAngle * deltaTime;
    updateViewMatrix();
}




