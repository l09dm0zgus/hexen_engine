//
// Created by vedme on 04.06.2024.
//
#include "EntitySettingsWindow.hpp"
#include <misc/cpp/imgui_stdlib.h>
#include <systems/graphics/RenderSystem.hpp>
#include <components/transform/TransformComponent.hpp>
#include <string>

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

	if (it == container->end())
	{
		return;
	}
	
	auto pos = it->getPosition();
	auto rot = it->getRotation();
	float layer = it->getLayer();

	if (ImGui::CollapsingHeader(it->getName().c_str(), ImGuiTreeNodeFlags_None))
	{
		if (ImGui::CollapsingHeader("Position", ImGuiTreeNodeFlags_None))
		{
			ImGui::Text(("Axis x: "s + std::to_string(pos.x)).c_str());
			ImGui::Text(("Axis y: "s + std::to_string(pos.y)).c_str());
			float newValue[2] = {0.0, 0.0};
			ImGui::InputFloat2("Edit position", newValue);
			if (auto temp = glm::vec2(newValue[0], newValue[1]); temp != pos)
			{
				it->setPosition(temp);
			}
		}
		if (ImGui::CollapsingHeader("Rotation", ImGuiTreeNodeFlags_None))
		{
			ImGui::Text(("Axis x: "s + std::to_string(rot.x)).c_str());
			ImGui::Text(("Axis y: "s + std::to_string(rot.y)).c_str());
			float newValue[2] = {0.0, 0.0};
			ImGui::InputFloat2("Edit rotation", newValue);
			if (auto temp = glm::vec2(newValue[0], newValue[1]); temp != pos)
			{
				it->setRotation(temp);
			}
		}
		if (ImGui::CollapsingHeader("Layer", ImGuiTreeNodeFlags_None))
		{
			ImGui::Text(("Game Layer: "s + std::to_string(it->getLayer())).c_str());
			float temp = 0.0;
			ImGui::InputFloat("Set layer", &temp);
			if (temp != layer){
				it->setLayer(temp);
			}
		}
	}
}