//
// Created by cx9ps3 on 02.01.23.
//

#pragma once
#include "../Buffers.hpp"
#include <core/Types.hpp>
#include <cstddef>


namespace hexen::engine::graphics::gl
{
	/**
    * @class GLVertexBuffer
    *
    * @brief The GLVertexBuffer class represents a vertex buffer object used in rendering vertex data.
    * @extends VertexBuffer
    * A vertex buffer object (VBO) is used to efficiently store vertex data in GPU memory. This class provides
    * functionality to create and manage a VBO.
    */

	class GLVertexBuffer : public VertexBuffer
	{
	public:

		/**
 		* @brief Class constructor that sets up an OpenGL vertex buffer object (VBO).
 		*
 		* This constructor generates a new VBO, binds it to the current context,
 		* populates it with data and finally unbinds it from the context.
 		*
 		* @param vertices An array of floating point values representing a vertex data.
 		* @param size The size of the vertex data in bytes. @note  correct size is count of vertices multiply by sizeof(<indices type>) of vertices type.
 		*/

		GLVertexBuffer(float *vertices, core::u32 size);

		/**
		*
    	* @brief Destructor of GLVertexBuffer class.
 		*
 		* This function deletes the buffer, releasing the memory that was used for this
 		* Vertex Buffer Object from the GPU.
 		*/

		~GLVertexBuffer() override;

		/**
 		* @brief A member function that binds the vertex buffer object to the current OpenGL context.
 		*
 		* This function is used whenever the vertex data stored in this buffer object is required for rendering.
 		*/

		void bind() const noexcept override;

		/**
 		* @brief A member function that unbinds the vertex buffer object from the current OpenGL context.
 		*
 		* After rendering the data, it is good practice to unbind the buffer to prevent accidental modification or misuse.
 		*/

		void unbind() const noexcept override;

	private:
		core::u32 object {0};
	};
}// namespace hexen::engine::graphics::gl