//
// Created by vedme on 04.06.2024.
//
#include "EntitySettingsWindow.hpp"
#include <misc/cpp/imgui_stdlib.h>
#include <systems/graphics/RenderSystem.hpp>
#include <components/transform/TransformComponent.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <core/logging/Log.hpp>
#include <spdlog/spdlog.h>
#include "../../logging/EditorCategories.hpp"

void hexen::editor::gui::EntitySettingsWindow::begin()
{
	HEXEN_ADD_TO_PROFILE()
}

void hexen::editor::gui::EntitySettingsWindow::draw()
{
	HEXEN_ADD_TO_PROFILE()
	ImGui::Begin(getName().c_str(), &isOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_HorizontalScrollbar);
	drawCurrentSettings();
	ImGui::End();
}

void hexen::editor::gui::EntitySettingsWindow::end()
{
	HEXEN_ADD_TO_PROFILE()
}

hexen::editor::gui::EntitySettingsWindow::EntitySettingsWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : GUIWindow(std::move(name), parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
	setSize(glm::vec2(400, 300));
	HEXEN_LOG_CALL(hexen::editor::logging::editorCategory, LogLevel::info, "Ia sosu bibu")
}

hexen::editor::gui::EntitySettingsWindow::EntitySettingsWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : GUIWindow(name, parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
	setSize(glm::vec2(400, 300));
}

void hexen::editor::gui::EntitySettingsWindow::setNode(std::shared_ptr<hexen::engine::entity::SceneEntity> Node)
{
	node = Node;
}

void hexen::editor::gui::EntitySettingsWindow::drawCurrentSettings()
{
	using namespace std::literals::string_literals;

	if (!node)
	{
		return;
	}
	ImGui::Text(node->getName().c_str());

	auto &ComponentRegestry = hexen::engine::systems::RenderSystem::getComponentRegistry();
	auto container = ComponentRegestry.getBaseComponentContainer<engine::components::TransformComponent>();

	auto it = std::find_if(container->begin(), container->end(), [this](hexen::engine::components::Component const &c)
			{ return c.getOwnerUUID() == node->getUUID(); });

	if (it != container->end())
	{
		static auto position = it->getPosition();
		static auto rotation = it->getRotation();
		static float layer = it->getLayer();

		if (ImGui::CollapsingHeader("Transform Component", ImGuiTreeNodeFlags_None))
		{
			if (ImGui::CollapsingHeader("Position", ImGuiTreeNodeFlags_None))
			{
				ImGui::Text(("Axis x: "s + std::to_string(position.x)).c_str());
				ImGui::Text(("Axis y: "s + std::to_string(position.y)).c_str());
				if (ImGui::InputFloat2("Position", glm::value_ptr(position)))
				{
					it->setPosition(position);
				}
			}
			if (ImGui::CollapsingHeader("Rotation", ImGuiTreeNodeFlags_None))
			{
				ImGui::Text(("Axis x: "s + std::to_string(rotation.x)).c_str());
				ImGui::Text(("Axis y: "s + std::to_string(rotation.y)).c_str());
				if (ImGui::InputFloat2("Rotation", glm::value_ptr(rotation)))
				{
					it->setRotation(rotation);
				}
			}
			if (ImGui::CollapsingHeader("Layer", ImGuiTreeNodeFlags_None))
			{
				ImGui::Text(("Game Layer: "s + std::to_string(layer)).c_str());
				if (ImGui::InputFloat("Layer ", &layer))
				{
					it->setLayer(layer);
				}
			}
		}
	}
}