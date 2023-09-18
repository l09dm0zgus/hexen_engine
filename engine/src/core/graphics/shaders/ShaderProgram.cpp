//
// Created by cx9ps3 on 03.01.23.
//

#include "ShaderProgram.hpp"
#include <SDL3/SDL.h>

#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif
#include <glm/gtc/type_ptr.hpp>


hexen::engine::graphics::gl::shader::ShaderProgram::ShaderProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
	vertexShaderFile.read(vertexShaderPath);
	fragmentShaderFile.read(fragmentShaderPath);
	compileVertexShader();
	compileFragmentShader();
	linkShaders();
}


void hexen::engine::graphics::gl::shader::ShaderProgram::compileVertexShader()
{
	vertexShaderText = vertexShaderFile.getContent();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	glCompileShader(vertexShader);
	showCompilerLog(vertexShader);
}


inline void hexen::engine::graphics::gl::shader::ShaderProgram::showCompilerLog(core::u32 shader) const noexcept
{
	core::i32 success {0};
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		SDL_Log("Error:Failed compile shader.What : %s", infoLog);
	}
}


inline void hexen::engine::graphics::gl::shader::ShaderProgram::compileFragmentShader()
{
	fragmentShaderText = fragmentShaderFile.getContent();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
	glCompileShader(fragmentShader);
	showCompilerLog(fragmentShader);
}


hexen::engine::graphics::gl::shader::ShaderProgram::~ShaderProgram()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void hexen::engine::graphics::gl::shader::ShaderProgram::linkShaders()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	showLinkerLog();
}


void hexen::engine::graphics::gl::shader::ShaderProgram::showLinkerLog() const noexcept
{
	core::i32 success {0};
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		SDL_Log("Error:Failed to link shader.What : %s", infoLog);
	}
}


void hexen::engine::graphics::gl::shader::ShaderProgram::use() const noexcept
{
	glUseProgram(shaderProgram);
}

void hexen::engine::graphics::gl::shader::ShaderProgram::setIntUniform(const std::string &uniformVariable, core::i32 value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, uniformVariable.c_str()), value);
}

void hexen::engine::graphics::gl::shader::ShaderProgram::setMatrix4Uniform(const std::string &uniformVariable, const glm::mat4 &matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniformVariable.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}


void hexen::engine::graphics::gl::shader::ShaderProgram::setVector4Uniform(const std::string &uniformVariable, const glm::vec4 &vector) const
{
	glUniform4d(glGetUniformLocation(shaderProgram, uniformVariable.c_str()), vector.x, vector.y, vector.z, vector.w);
}


void hexen::engine::graphics::gl::shader::ShaderProgram::setVector3Uniform(const std::string &uniformVariable, const glm::vec3 &vector) const
{
	glUniform3f(glGetUniformLocation(shaderProgram, uniformVariable.c_str()), vector.x, vector.y, vector.z);
}
