//
// Created by cx9ps3 on 19.01.23.
//

#ifndef BATTLEBLAZE_RENDERCOMPONENT_H
#define BATTLEBLAZE_RENDERCOMPONENT_H
#include "../Component.h"
#include <glm/glm.hpp>
#include <iostream>

namespace comp::rend
{
    class RenderComponent : public Component
    {
    public:
        RenderComponent() = default;
        ~RenderComponent() = default;
        RenderComponent(const RenderComponent& renderComponent) = default;
        RenderComponent(RenderComponent &&) = default;
        RenderComponent& operator=(RenderComponent&& renderComponent) = default;
        RenderComponent& operator=(const RenderComponent &renderComponent) = default;

        template<class T> void setProjectionMatrix(T&& newProjection) noexcept
        {
            projection = std::forward<T>(newProjection);
        };
        template<class T> void setViewMatrix(T &&newView) noexcept
        {
            view = std::forward<T>(newView);
        };
        template<class T> void setTransformMatrix(T&& newTransform) noexcept
        {
            transform = std::forward<T>(newTransform);
        };

        glm::mat4 getProjectionMatrix() const noexcept;
        glm::mat4 getViewMatrix() const noexcept;
        glm::mat4 getTransformMatrix() const noexcept;

        virtual void start() override;
        virtual void update(float deltaTime) override;
        virtual void draw() = 0;

    private:
        glm::mat4 projection{1.0f};
        glm::mat4 view{1.0f};
        glm::mat4 transform{1.0f};
    };
}



#endif //BATTLEBLAZE_RENDERCOMPONENT_H