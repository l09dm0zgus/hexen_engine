//
// Created by cx9ps3 on 13.07.2023.
//

#include "DrawGridCommand.hpp"
#include "GridComponent.hpp"
#include <graphics/render_commands/RenderPipeline.hpp>

hexen::editor::components::graphics::GridComponent::GridComponent(const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> &shaderAssets, const glm::vec3 &newColor, const glm::vec2 &size, const glm::vec2 &unitSize, hexen::engine::graphics::RenderPipelineID renderPipelineId) : shaderAssets(shaderAssets)
{
	HEXEN_ADD_TO_PROFILE();
	grid = hexen::engine::core::memory::make_shared<hexen::engine::core::Grid>(size,unitSize);

	if (grid != nullptr)
	{
		auto vertices = createGridVertices(grid);
		auto indices = createGridIndices(grid);

		auto renderHandle = engine::graphics::RenderPipeline::addCommandToQueue<DrawGridCommand>(renderPipelineId, RenderGridData(vertices, indices, shaderAssets, newColor));
		drawGridCommand = engine::graphics::RenderPipeline::getCommandByType<DrawGridCommand>(renderPipelineId, renderHandle);
	}
}

void hexen::editor::components::graphics::GridComponent::setViewAndProjectionMatrices(const glm::mat4 &view, const glm::mat4 &projection)
{
	HEXEN_ADD_TO_PROFILE();
	drawGridCommand->view = view;
	drawGridCommand->projection = projection;
}

void hexen::editor::components::graphics::GridComponent::setTransformMatrix(const glm::mat4 &transform)
{
	HEXEN_ADD_TO_PROFILE();
	drawGridCommand->transform = transform;
}

std::vector<glm::vec3> hexen::editor::components::graphics::GridComponent::createGridVertices(const std::shared_ptr<hexen::engine::core::Grid> &grid)
{
	HEXEN_ADD_TO_PROFILE();
	std::vector<glm::vec3> vertices;

	for (hexen::engine::core::i32 j = 0; j <= grid->getSize().y; ++j)
	{
		for (hexen::engine::core::i32 i = 0; i <= grid->getSize().x; ++i)
		{
			auto x = (float) i * grid->getUnitSize().x  / grid->getUnitSize().x;
			auto y =  (float) j * grid->getUnitSize().y / grid->getUnitSize().x;
			auto z = 0;
			vertices.emplace_back(x, y, z);
		}
	}
	return vertices;
}

std::vector<glm::uvec4> hexen::editor::components::graphics::GridComponent::createGridIndices(const std::shared_ptr<hexen::engine::core::Grid> &grid)
{
	HEXEN_ADD_TO_PROFILE();
	std::vector<glm::uvec4> indices;

	for (hexen::engine::core::i32 j = 0; j < grid->getSize().y; ++j)
	{
		for (hexen::engine::core::i32 i = 0; i < grid->getSize().x; ++i)
		{

			hexen::engine::core::u32 row1 = j * (grid->getSize().x + 1);
			hexen::engine::core::u32 row2 = (j + 1) * (grid->getSize().x + 1);

			indices.emplace_back(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1);
			indices.emplace_back(row2 + i + 1, row2 + i, row2 + i, row1 + i);
		}
	}

	return indices;
}

void hexen::editor::components::graphics::GridComponent::setSize(const glm::vec2 &newSize)
{
	HEXEN_ADD_TO_PROFILE();
	grid->resize(newSize);
	auto vertices = createGridVertices(grid);
	auto indices = createGridIndices(grid);
	drawGridCommand->resize(RenderGridData(vertices, indices,shaderAssets,color));
}

void hexen::editor::components::graphics::GridComponent::setUnitSize(const glm::vec2 &newUnitSize)
{
	HEXEN_ADD_TO_PROFILE();
	grid->setUnitSize(newUnitSize);
	auto vertices = createGridVertices(grid);
	auto indices = createGridIndices(grid);
	drawGridCommand->resize(RenderGridData(vertices, indices,shaderAssets,color));
}

void hexen::editor::components::graphics::GridComponent::setLineWidth(float lineWidth)
{
	HEXEN_ADD_TO_PROFILE();
	drawGridCommand->lineWidth = lineWidth;
}
