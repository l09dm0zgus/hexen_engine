//
// Created by cx9ps3 on 19.05.2023.
//

#include "SceneEntity.hpp"
#include "../../systems/graphics/RenderSystem.hpp"
#include "../profiling/Profiling.hpp"
#include <algorithm>

hexen::engine::entity::SceneEntity::SceneEntity(std::string name) : hexen::engine::entity::Entity(), name(std::move(name))
{
	HEXEN_ADD_TO_PROFILE();
	handleForTransformComponent = systems::RenderSystem::registerNewComponent<components::TransformComponent>();
	transformComponent = systems::RenderSystem::getComponentInstanceByHandle<components::TransformComponent>(handleForTransformComponent);
}
hexen::engine::entity::SceneEntity::SceneEntity(std::string name, const std::string &UUID) : hexen::engine::entity::Entity(UUID), name(std::move(name))
{
	HEXEN_ADD_TO_PROFILE();
	handleForTransformComponent = systems::RenderSystem::registerNewComponent<components::TransformComponent>();
	transformComponent = systems::RenderSystem::getComponentInstanceByHandle<components::TransformComponent>(handleForTransformComponent);
}

hexen::engine::entity::SceneEntity *hexen::engine::entity::SceneEntity::getParent() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return parent;
}

void hexen::engine::entity::SceneEntity::setParent(hexen::engine::entity::SceneEntity *newParent)
{
	HEXEN_ADD_TO_PROFILE();
	parent = newParent;
}

void hexen::engine::entity::SceneEntity::forceUpdateTransformMatrix()
{
	HEXEN_ADD_TO_PROFILE();
	if (parent != nullptr)
	{
		transformComponent->updateTransformMatrix(parent->transformComponent->getTransformMatrix());
	}
	else
	{
		transformComponent->updateTransformMatrix();
	}
}

void hexen::engine::entity::SceneEntity::updateTransformMatrix()
{
	HEXEN_ADD_TO_PROFILE();
	if (transformComponent->isDirty())
	{
		forceUpdateTransformMatrix();
		return;
	}

	for (auto &&child : childrens)
	{
		child.second->updateTransformMatrix();
	}
}

void hexen::engine::entity::SceneEntity::removeChild(const std::string &name)
{
	HEXEN_ADD_TO_PROFILE();
	if (hasChildrens())
	{
		auto it = std::find_if(childrens.cbegin(), childrens.cend(), [&name](const std::pair<std::basic_string<char>, std::shared_ptr<SceneEntity>>& c){return c.second->name == name;});

		if (it != childrens.cend())
		{
			childrens.erase(it->first);
		}
	}
}

std::string hexen::engine::entity::SceneEntity::getName() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return name;
}

void hexen::engine::entity::SceneEntity::removeChildByUUID(const std::string &UUID)
{
	HEXEN_ADD_TO_PROFILE();
	childrens.erase(UUID);
}

bool hexen::engine::entity::SceneEntity::hasChildrens() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return !childrens.empty();
}

std::unordered_map<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>> hexen::engine::entity::SceneEntity::getChildrens() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return childrens;
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::entity::SceneEntity::getChild(const std::string &name) const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	auto it = std::find_if(childrens.cbegin(), childrens.cend(), [&name](const std::pair<std::basic_string<char>, std::shared_ptr<SceneEntity>>& c){return c.second->name == name;});

	if (it == childrens.cend())
	{
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::entity::SceneEntity::getChildByUUID(const std::string &UUID) const noexcept
{
	HEXEN_ADD_TO_PROFILE();

	auto child = childrens.at(UUID);
	if (child != nullptr)
	{
		return child;
	}
	else
	{
		return nullptr;
	}
}

std::unordered_map<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>>::const_iterator hexen::engine::entity::SceneEntity::find(const std::string &name) const
{
	HEXEN_ADD_TO_PROFILE();
	auto it = std::find_if(childrens.cbegin(), childrens.cend(), [&name](const auto &keyValue)
			{ return name == keyValue.second->getName(); });
	return it;
}

void hexen::engine::entity::SceneEntity::changeParent(std::shared_ptr<SceneEntity> &newParent)
{
	HEXEN_ADD_TO_PROFILE();

	if (newParent != nullptr && newParent.get() != parent && newParent.get() != this)
	{
		if (parent != nullptr)
		{
			auto child = parent->getChildByUUID(getUUID());
			if (child != nullptr)
			{
				newParent->addChildByPointer(child);
				parent->removeChildByUUID(getUUID());
			}
		}
		else
		{
			newParent->addChildByPointer(std::shared_ptr<SceneEntity>(this));
		}
	}

	parent = newParent.get();
}

void hexen::engine::entity::SceneEntity::addChildByPointer(const std::shared_ptr<SceneEntity> &newChild)
{
	HEXEN_ADD_TO_PROFILE();
	childrens.insert({newChild->getUUID(), newChild});
}

bool hexen::engine::entity::SceneEntity::isNodeExist(const std::shared_ptr<hexen::engine::entity::SceneEntity> &node, const std::string &UUID)
{
	HEXEN_ADD_TO_PROFILE();

	if (node->getUUID() == UUID)
	{
		return true;
	}
	else
	{
		for (const auto &child : node->childrens)
		{
			if (SceneEntity::isNodeExist(child.second, UUID))
			{
				return true;
			}
		}
	}
	return false;
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::entity::SceneEntity::getNode(const std::shared_ptr<hexen::engine::entity::SceneEntity> &node, const std::string &UUID)
{
	HEXEN_ADD_TO_PROFILE();

	if (node->getUUID() == UUID)
	{
		return node;
	}
	else
	{
		for (const auto &child : node->childrens)
		{
			auto result = SceneEntity::getNode(child.second, UUID);
			if (result != nullptr)
			{
				return result;
			}
		}
	}
	return nullptr;
}

bool hexen::engine::entity::SceneEntity::isDescendantExist(const std::string &descendantUUID)
{
	HEXEN_ADD_TO_PROFILE();

	auto it = childrens.find(descendantUUID);
	if (it != childrens.end())
	{
		return true;
	}
	else
	{
		for (const auto &child : childrens)
		{
			auto isExist = child.second->isDescendantExist(descendantUUID);
			if (isExist)
			{
				return isExist;
			}
		}
	}
	return false;
}

bool hexen::engine::entity::SceneEntity::searchNode(const std::shared_ptr<hexen::engine::entity::SceneEntity> &node, const std::string &searchQuery, std::unordered_map<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>> &foundedNodes)
{
	HEXEN_ADD_TO_PROFILE();

	auto found = node->getName().find(searchQuery);

	if (found != std::string::npos)
	{
		foundedNodes.insert({node->getUUID(), node});
		return true;
	}
	else
	{
		for (const auto &child : node->childrens)
		{
			auto result = SceneEntity::searchNode(child.second, searchQuery, foundedNodes);
			if (result)
			{
				return result;
			}
		}
	}
	return false;
}
