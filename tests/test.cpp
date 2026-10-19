#include <Objects/Camera/Camera.hpp>
#include <Objects/Model/Model.hpp>
#include <Renderer/Renderer.hpp>
#include <ResourceMan/ResourceMan.hpp>
#include <Shader/Shader.hpp>
#include <Renderer/RenderObjects.hpp>
#include <ShortNamespace.hpp>

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

int main() {
	SOL::Renderer render("toitel", 800, 600);
	SOL::ResourceMan resman;
	SOL::Shader shader(vertex_shader, fragment_shader);
	SOL::Camera cam(SOL::CameraProperties {
		.initial_pos = {-1.0f, 1.0f, 1.0f},
		.looking_at = {0.0f, 0.0f, 0.0f},
		.fov = glm::radians(60.0f),
		.aspect_ratio = 800.0f / 600.0f,
	});

	unsigned mesh_resource_key = resman.OwnResource(cube_mesh, sizeof(cube_mesh));
	auto mesh_resource = resman.FetchCasted<float>(mesh_resource_key);
	SOL::Model model(mesh_resource, SOL::NoTexture);

	render.AttachShader(shader);
	render.AttachRenderObject(&model);
	render.AttachRenderObject(&cam);
	render.AddTickEvent(renderer_tick);

	cam.Attach();

    while (!render.GetShouldClose()) {
		render.Tick();
		model.Rotate(0.01f, SOL::XAxis);
		model.SetPosition({ std::sin(glfwGetTime()), 0.0f, 0.0f });
		// model.Translate({ 0.01f, 0.0f, 0.0f });
	}

	return 0;
}

bool renderer_tick(SOL::Renderer& render) {
	if (glfwGetKey(render.GetGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		render.SetShouldClose(true);
	}

	return true;
}
