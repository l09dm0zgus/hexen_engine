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
        explicit SceneEntity(std::string name);
        SceneEntity(std::string name, const std::string &UUID);
        std::string getName() const noexcept;
        SceneEntity* getParent() const noexcept;
        void setParent(SceneEntity *newParent);
        std::shared_ptr<comp::TransformComponent> transformComponent;
        bool hasChildrens() const noexcept;
        core::HashTable<std::string,std::shared_ptr<SceneEntity>> getChildrens() const noexcept;
        std::shared_ptr<SceneEntity> getChild(const std::string &name) const noexcept;
        std::shared_ptr<SceneEntity> getChildByUUID(const std::string &UUID) const noexcept;

        //helper static methods for finding nodes in Scene
        static bool isNodeExist(const std::shared_ptr<ent::SceneEntity> &node,const std::string &UUID);
        static std::shared_ptr<SceneEntity> getNode(const std::shared_ptr<ent::SceneEntity> &node,const std::string &UUID);

        template<class T, class... Ts> void addChild(Ts&&... params)
        {
            childrens.set(generateUUIDV4(),core::mem::make_shared<T>(params...));
        }

        template<class T> void addChild(T &&entityName)
        {
            std::string childUUID = generateUUIDV4();
            auto child = core::mem::make_shared<SceneEntity>(entityName,childUUID);
            childrens.set(childUUID,child);
            childrens[childUUID]->setParent(this);
        }

        void addChildByPointer(const std::shared_ptr<SceneEntity> &newChild);
        void forceUpdateTransformMatrix();
        void updateTransformMatrix();
        void changeParent(std::shared_ptr<SceneEntity> &newParent);
        void removeChild(const std::string &name);
        void removeChildByUUID(const std::string &UUID);
    private:
        std::string name;
        core::HashTable<std::string,std::shared_ptr<SceneEntity>> childrens;
        SceneEntity *parent{nullptr};
        core::HashTable<std::string, std::shared_ptr<ent::SceneEntity>>::ConstIterator find(const std::string &name) const;
    };
}

#endif //BATTLEBLAZE_SCENEENTITY_H
