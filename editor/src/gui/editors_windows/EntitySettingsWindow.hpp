//
// Created by vedme on 04.06.2024.
//

#pragma once
#include "GUIWindow.hpp"
#include "entity/scene/SceneEntity.hpp"

namespace hexen::editor::gui {
	class EntitySettingsWindow : public GUIWindow
	{
	private:

		bool isOpen {true};

		std::shared_ptr<hexen::engine::entity::SceneEntity> node{nullptr};

		void drawCurrentSettings();

		void drawAddComponentMenu();

	public:
		EntitySettingsWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace);

		EntitySettingsWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace);

		void begin() override;

		void draw() override;

		void end() override;

		void setNode(std::shared_ptr<hexen::engine::entity::SceneEntity> Node);

	};
}