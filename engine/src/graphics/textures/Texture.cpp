//
// Created by cx9ps3 on 08.10.2023.
//

#include "Texture.hpp"
#include "../render_context/RenderContext.hpp"
#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLTexture2D.hpp"
#endif

std::shared_ptr<hexen::engine::graphics::Texture2D> hexen::engine::graphics::Texture2D::create(const std::string &path,TextureFilter filter)
{

	switch (RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create Vertex Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_shared<gl::GLTexture2D>(path,filter);
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}

	return nullptr;
}