//
// Created by cx9ps3 on 10.01.23.
//

#include "CameraComponent.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <SDL3/SDL.h>
#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif
#include "../../systems/InputHelper.hpp"
#include <render_commands/RenderPipeline.hpp>
#include <render_commands/ViewportCommand.hpp>


void hexen::engine::components::graphics::CameraComponent::updateViewMatrix()
{
	HEXEN_ADD_TO_PROFILE();
	glm::vec3 direction;
	direction.x = cos(glm::radians(currentYawAngle)) * cos(glm::radians(currentPitchAngle));
	direction.y = sin(glm::radians(currentPitchAngle));
	direction.z = sin(glm::radians(currentYawAngle)) * cos(glm::radians(currentPitchAngle));

	cameraTarget = glm::normalize(direction);

	cameraRight = glm::normalize(glm::cross(cameraTarget, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraTarget));
}

hexen::engine::components::graphics::CameraComponent::CameraComponent(core::i32 viewportWidth, core::i32 viewportHeight, float FOV)
{
	HEXEN_ADD_TO_PROFILE();
	this->FOV = FOV;
	updateProjectionMatrix(viewportWidth, viewportHeight);
	updateViewMatrix();
}

glm::mat4 hexen::engine::components::graphics::CameraComponent::getViewMatrix()
{
	HEXEN_ADD_TO_PROFILE();
	return glm::lookAt(position, position + cameraTarget, cameraUp);
}


glm::mat4 hexen::engine::components::graphics::CameraComponent::getProjectionMatrix()
{
	HEXEN_ADD_TO_PROFILE();
	return projection;
}

void hexen::engine::components::graphics::CameraComponent::updateProjectionMatrix(core::u32 newWindowWidth, core::u32 newWindowHeight)
{
	HEXEN_ADD_TO_PROFILE();
	engine::graphics::RenderPipeline::executeCommandNow<engine::graphics::ViewportCommand>(engine::graphics::RenderPipelineID::MAIN_PIPELINE, glm::ivec4(0, 0, newWindowWidth, newWindowHeight));
	projection = glm::perspective(glm::radians(FOV), static_cast<float>(newWindowWidth) / static_cast<float>(newWindowHeight), 0.1f, 100.0f);
}

void hexen::engine::components::graphics::CameraComponent::setYaw(float yawAngle)
{
	HEXEN_ADD_TO_PROFILE();
	currentYawAngle = yawAngle;
	updateViewMatrix();
}

void hexen::engine::components::graphics::CameraComponent::setPitch(float pitchAngle)
{
	HEXEN_ADD_TO_PROFILE();
	currentPitchAngle = pitchAngle;
	updateViewMatrix();
}

float hexen::engine::components::graphics::CameraComponent::getYaw() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return currentYawAngle;
}

float hexen::engine::components::graphics::CameraComponent::getPitch() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return currentPitchAngle;
}
