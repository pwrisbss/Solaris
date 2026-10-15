#ifndef SOLARIS_SHADER_H
#define SOLARIS_SHADER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Solaris {

/**
 * @brief Solaris Shader Class.
 *
 * @details Solaris's C++ wrapper for the OpenGL shader system. Each `Shader` object represents
 * an OpenGL shader pipeline (currently only supports one vertex shader and one fragment shader).
 * 
 */
class Shader {
private:
	unsigned vertex_shader;
	unsigned fragment_shader;
	unsigned shader_program;

public:
	/**
	 * @brief Construct a new Shader object
	 * 
	 * @param vertex_shader_source GLSL Source Code for the Vertex Shader
	 * @param fragment_shader_source GLSL Source Code for the Fragment Shader
	 */
	Shader(const char * vertex_shader_source, const char * fragment_shader_source);
	~Shader();

	/**
	 * @fn void Solaris::Shader::Use()
	 * @brief "Use" the shader program.
	 *
	 * @details Set this `Shader` object as the active shader. Equivalent to `glUseProgram(shader.GetShaderProg())`.
	 * @see Solaris::Shader::GetShaderProg()
	 * 
	 */
	void Use();

	/**
	 * @fn unsigned Solaris::Shader::GetShaderProg()
	 * @brief Get the shader program ID
	 * 
	 * @details Return the shader pipeline's program ID used by OpenGL to identify it. This is usually not needed
	 * unless you plan on implementing custom shader functionality or other rendering-related things.
	 * @return unsigned int
	 */
	unsigned GetShaderProg();
};

}

#endif // SOLARIS_SHADER_H