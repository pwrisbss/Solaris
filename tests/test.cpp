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
		.position = {0.0f, 1.0f, 0.0f},
		.looking_at = {0.0f, 0.0f, 0.0f},
		.fov = glm::radians(60.0f),
		.aspect_ratio = 800.0f / 600.0f,
	});

	unsigned mesh_resource_key = resman.OwnResource(cube_mesh, sizeof(cube_mesh));
	auto mesh_resource = resman.FetchCasted<float>(mesh_resource_key);
	SOL::Model model0(mesh_resource, SOL::NoTexture);
	// SOL::Model model1(mesh_resource, SOL::NoTexture);
	// SOL::Model model2(mesh_resource, SOL::NoTexture);
	// SOL::Model model3(mesh_resource, SOL::NoTexture);
	model0.SetPosition({ 0.0f, 0.0f, 0.0f });
	// model1.SetPosition({ 1.0f, 1.0f, 0.5f });
	// model2.SetPosition({ -1.0f, -1.0f, -0.5f });
	// model3.SetPosition({ 1.0f, 0.0f, 0.5f });

	render.AttachShader(shader);
	render.AttachRenderObject(&model0);
	// render.AttachRenderObject(&model1);
	// render.AttachRenderObject(&model2);
	// render.AttachRenderObject(&model3);
	render.AttachRenderObject(&cam);
	render.AddTickEvent(renderer_tick);

	cam.Attach();

    while (!render.GetShouldClose()) {
		render.Tick();
		// model0.Rotate(0.01f, SOL::XAxis);
		// model0.SetPosition({ std::sin(glfwGetTime()), 0.0f, 0.0f });
		// model.Translate({ 0.01f, 0.0f, 0.0f });
		cam.ApplyProperties(SOL::CameraProperties {
		.position = {0.0f, 0.0f, std::sin(glfwGetTime()) + 0.5f},
		.looking_at = {0.0f, 0.0f, 0.0f},
		.fov = glm::radians(60.0f),
		.aspect_ratio = 800.0f / 600.0f,
	});
	}

	return 0;
}

bool renderer_tick(SOL::Renderer& render) {
	if (glfwGetKey(render.GetGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		render.SetShouldClose(true);
	}

	return true;
}
