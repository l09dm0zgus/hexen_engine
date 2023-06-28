//
// Created by cx9ps3 on 19.05.2023.
//

#ifndef BATTLEBLAZE_SCENEENTITY_H
#define BATTLEBLAZE_SCENEENTITY_H
#include "../Entity.h"
#include "../../core/Types.h"
#include "../../components/transform/TransformComponent.h"

namespace ent
{
    class SceneEntity : public Entity
    {
    public:
        SceneEntity(std::string name);
        SceneEntity(std::string name, const std::string &UUID);
        std::string getName() const noexcept;
        SceneEntity* getParent() const noexcept;
        void setParent(SceneEntity *newParent);
        std::shared_ptr<comp::TransformComponent> transformComponent;
        bool hasChildrens() const noexcept;
        core::HashTable<std::string,std::shared_ptr<SceneEntity>> getChildrens() const noexcept;
        template<class T, class... Ts> void addChild(Ts&&... params);
        template<class T> void addChild(T &&name);
        void forceUpdateTransformMatrix();
        void updateTransformMatrix();
        void detachFromParent();
        void removeChild(const std::string &name);
        void removeChildByUUID(const std::string &UUID);
    private:
        std::string name;
        core::HashTable<std::string,std::shared_ptr<SceneEntity>> childrens;
        SceneEntity *parent{nullptr};
    };
}

#endif //BATTLEBLAZE_SCENEENTITY_H
