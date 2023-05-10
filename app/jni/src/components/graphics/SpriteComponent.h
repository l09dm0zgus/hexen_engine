//
// Created by cx9ps3 on 04.01.23.
//

#ifndef BATTLEBLAZE_SPRITECOMPONENT_H
#define BATTLEBLAZE_SPRITECOMPONENT_H
#include "../../core/graphics/shaders/Shaders.h"
#include "../../core/graphics/VertexBufferObject.h"
#include "../../core/graphics/VertexArrayObject.h"
#include "../../core/graphics/RectangleVertices.h"
#include "../../core/graphics/VertexAttributes.h"
#include "../../core/graphics/texture/Texture.h"
#include "../../core/transform/Transform.h"
#include <vector>
#include "RenderComponent.h"
namespace comp::rend
{
    class SpriteComponent : public RenderComponent
    {
    public:
        ~SpriteComponent();
        void create(const std::string &vertexShaderPath , const std::string &fragmentShaderPath) override;
        void draw() override;
        void addTexture(const std::string &pathToImage);
        void  setTransform(const Transform &transform);
        Transform getTransform();
    private:
        Transform transform;
        std::vector<core::rend::Texture*> textures;
        core::rend::VertexBufferObject *VBO{nullptr};
        core::rend::RectangleVertices vertices;
    protected:
        core::rend::VertexAttributes attributes;
        core::rend::VertexArrayObject *VAO{nullptr};
        core::rend::shader::ShaderProgram *shaderProgram{nullptr};
        void bindTextures();
    };
}
#endif //BATTLEBLAZE_SPRITECOMPONENT_H
