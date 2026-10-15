#include "Shader.hpp"

namespace Solaris {

Shader::Shader(const char * vertex_shader_source, const char * fragment_shader_source) :
	vertex_shader(glCreateShader(GL_VERTEX_SHADER)),
	fragment_shader(glCreateShader(GL_FRAGMENT_SHADER)),
	shader_program(glCreateProgram()) {
	// this->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	// this->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	// this->shader_program = glCreateProgram();
	int success;
	char info_log[1024];

	// vertex shader
	glShaderSource(this->vertex_shader, 1, &vertex_shader_source, nullptr);
	glCompileShader(this->vertex_shader);
	glGetShaderiv(this->vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		// TODO add error handling
		// the official solaris way
		glGetShaderInfoLog(this->vertex_shader, 1024, nullptr, info_log);
		std::cout << info_log;
	}

	// fragment shader
	glShaderSource(this->fragment_shader, 1, &fragment_shader_source, nullptr);
	glCompileShader(this->fragment_shader);
	glGetShaderiv(this->fragment_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		// TODO add error handling
		// the official solaris way
		glGetShaderInfoLog(this->fragment_shader, 1024, nullptr, info_log);
		std::cout << info_log;
	}

	// shader program
	glAttachShader(this->shader_program, this->vertex_shader);
	glAttachShader(this->shader_program, this->fragment_shader);
	glLinkProgram(this->shader_program);
	glGetProgramiv(this->shader_program, GL_LINK_STATUS, &success);

	if (!success) {
		// TODO add error handling
		// the official solaris way
		glGetProgramInfoLog(this->shader_program, 1024, nullptr, info_log);
		std::cout << info_log;
	}
}

Shader::~Shader() {
	glDeleteShader(this->vertex_shader);
	glDeleteShader(this->fragment_shader);
	glDeleteProgram(this->shader_program);
}

void Shader::Use() {
	glUseProgram(this->shader_program);
}

unsigned Shader::GetShaderProg() {
	return this->shader_program;
}

}