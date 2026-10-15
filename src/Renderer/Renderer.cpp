#include "Renderer.hpp"

namespace Solaris {

Renderer::Renderer(std::string window_title, int window_width, int window_height, Shader& shader) :
	shader(new Shader(shader)),
	global_transform(1.0f) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// TODO proper error handling
		std::cout << "renderer creation failed!";
		
		glfwTerminate();
		return;
	}

	glEnable(GL_DEPTH_TEST);

	this->shader->Use();
}

Renderer::Renderer(std::string window_title, int window_width, int window_height) : 
	global_transform(1.0f) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// TODO proper error handling
		std::cout << "renderer creation failed!";
		
		glfwTerminate();
		return;
	}
	glViewport(0, 0, 800, 600);

	glEnable(GL_DEPTH_TEST);
}

void Renderer::Tick() {
	// tick events
	for (auto ev : this->events) {
		if (!ev(*this)) {
			// TODO add proper error handling
			std::cout << "W: Render tick event returned false! Possible error!\n";
		}
	}

	// render objects
	for (auto obj : this->objects) {
		// render
		if (obj->renderable) {
			if (!obj->Render(*this)) {
				std::cout << "W: RenderObject::Render() returned false! Possible error!\n";
			}
		}

		// tick
		if (obj->tickable) {
			if (!obj->Tick(*this)) {
				std::cout << "W: RenderObject::Tick() returned false! Possible error!\n";
			}
		}
	}

	glfwSwapBuffers(this->window);
	glClear(GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();
}

Renderer::~Renderer() {
	for (auto obj : this->objects) {
		if (obj->destructible) {
			if (!obj->Destroy(*this)) {
				std::cout << "W: RenderObject::Destroy() returned false! Possible error!\n";
			}
		}
	}

	// cleanup
	delete this->shader;
	glfwTerminate();
}

// Getters
bool Renderer::GetShouldClose() {
	// checks if the renderer should close
	return glfwWindowShouldClose(this->window);
}

GLFWwindow * Renderer::GetGLFWWindow() {
	return this->window;
}

Shader * Renderer::GetShaderPtr() {
	return this->shader;
}

// Setters
void Renderer::SetShouldClose(bool value) {
	glfwSetWindowShouldClose(this->window, value);
}

void Renderer::SetGlobalTransform(glm::mat4 set_to) {
	this->global_transform = set_to;
	this->shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->shader->GetShaderProg(), "global_transform"),
		1, GL_FALSE, glm::value_ptr(this->global_transform));
}

void Renderer::AttachRenderObject(RenderObject * object) {
	this->objects.push_back(object);

	unsigned current_idx = this->objects.size() - 1;

	if (this->objects[current_idx]->constructible) {
		this->objects[current_idx]->Construct(*this);
	}
}

void Renderer::AttachShader(Shader &shader) {
	this->shader = new Shader(shader);
}

}
