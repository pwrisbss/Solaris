#include "Objects/UI/UI.hpp"
#include <Objects/Camera/Camera.hpp>
#include <Objects/Model/Model.hpp>
#include <Renderer/Renderer.hpp>
#include <ResourceMan/ResourceMan.hpp>
#include <Shader/Shader.hpp>
#include <Renderer/RenderObjects.hpp>
#include <ShortNamespace.hpp>
#include <chrono>

float cube_mesh[] = {
    -0.5f, -0.5f, -0.5f,//  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,//  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,//  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,//  0.0f, 0.0f,
//
    -0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,//  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,//  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,//  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,//  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
//
    -0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,
//
     0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,
//
    -0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,//  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,//  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,//  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,//  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,//  0.0f, 1.0f,
//
    -0.5f,  0.5f, -0.5f,//  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,//  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,//  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,//  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,//  0.0f, 1.0f
};

const char vertex_shader[] = R"(
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 global_transform;
uniform mat4 model_transform;

void main() {
	gl_Position = global_transform * model_transform * vec4(aPos, 1.0f);
}
)";

const char fragment_shader[] = R"(
#version 330 core

out vec4 fragCol;

void main() {
	fragCol = vec4(0.1f, 1.0f, 0.25f, 1.0f);
}
)";

bool renderer_tick(SOL::Renderer& render);
void mouse_mvmt(GLFWwindow * wnd, double x, double y);

SOL::Camera cam(SOL::CameraProperties {
	.position = {0.0f, 1.0f, 0.0f},
	.looking_at = {0.0f, 0.0f, 0.0f},
	.fov = glm::radians(60.0f),
	.aspect_ratio = 800.0f / 600.0f,
});

int main() {
	auto start_time = std::chrono::system_clock::now();
	SOL::Renderer * render = new SOL::Renderer("toitel", 800, 600);
	SOL::ResourceMan resman;
	SOL::Shader shader(vertex_shader, fragment_shader);

	unsigned mesh_resource_key = resman.OwnResource(cube_mesh, sizeof(cube_mesh));
	auto mesh_resource = resman.FetchCasted<float>(mesh_resource_key);
	SOL::Model model0(mesh_resource, SOL::NoTexture);
	model0.SetPosition({ 0.0f, 0.0f, 0.0f });

	render->AttachShader(shader);
	render->AttachRenderObject(&model0);
	render->AttachRenderObject(&cam);
	render->AddTickEvent(renderer_tick);
	glfwSetCursorPosCallback(render->GetGLFWWindow(), mouse_mvmt);
	glfwSetInputMode(render->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	cam.Attach();
	cam.SetPosition({ 0.0f, 0.0f, 2.0f });

	auto end_time = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end_time - start_time;
	std::cout << "load time: " << elapsed.count() << "s\n";
    while (!render->GetShouldClose()) {
		render->Tick();
	}

	start_time = std::chrono::system_clock::now();
	
	delete render;

	end_time = std::chrono::system_clock::now();
	elapsed = end_time - start_time;
	std::cout << "unload time: " << elapsed.count() << "s\n";

	return 0;
}

float moveSpeed = 0.1f;
bool renderer_tick(SOL::Renderer& render) {
	if (glfwGetKey(render.GetGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		render.SetShouldClose(true);
	}

	if (glfwGetKey(render.GetGLFWWindow(), GLFW_KEY_W)) {
		cam.Translate(moveSpeed * cam.properties.front_vector);
	}
	if (glfwGetKey(render.GetGLFWWindow(), GLFW_KEY_A)) {
		cam.Translate(-moveSpeed * cam.properties.right_vector);
	}
	if (glfwGetKey(render.GetGLFWWindow(), GLFW_KEY_S)) {
		cam.Translate(-moveSpeed * cam.properties.front_vector);
	}
	if (glfwGetKey(render.GetGLFWWindow(), GLFW_KEY_D)) {
		cam.Translate(moveSpeed * cam.properties.right_vector);
	}
	if (glfwGetKey(render.GetGLFWWindow(), GLFW_KEY_1)) {
		cam.Detach();
	}
	if (glfwGetKey(render.GetGLFWWindow(), GLFW_KEY_2)) {
		cam.Attach();
	}

	return true;
}

bool isFirstMove = true;
float mouseLastX;
float mouseLastY;
float sensitivity = 2.5f;
void mouse_mvmt(GLFWwindow * wnd, double x, double y) {
	if (isFirstMove) {
		mouseLastX = x;
		mouseLastY = y;

		isFirstMove = false;
		return;
	}

	float dx = x - mouseLastX;
	float dy = y - mouseLastY;

	cam.Rotate(-dy * sensitivity, dx * sensitivity);

	mouseLastX = x;
	mouseLastY = y;
}