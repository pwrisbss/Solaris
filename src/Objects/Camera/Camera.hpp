#ifndef SOLARIS_CAMERA_H
#define SOLARIS_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Renderer/Renderer.hpp>
#include <Renderer/RenderObjects.hpp>

namespace Solaris {

typedef struct CameraProperties {
	glm::vec3 initial_pos = {0.0f, 0.0f, 0.0f};
	glm::vec3 up_vector = {0.0f, 1.0f, 0.0f};
	glm::vec3 front_vector;
	glm::vec3 looking_at;
	
	// projection properties
	bool perspective = true;
	float near_clip = 0.1f;
	float far_clip = 1000.0f;

	// perspective-specific
	float fov = 60.0f;
	float aspect_ratio = 800.0f / 600.0f;

	// ortho-specific
	float left;
	float right;
	float bottom;
	float top;
} CameraProperties;

class Camera : public RenderObject {
private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 looking_at;
	glm::vec3 cam_front;
	glm::mat4 projection;
	glm::mat4 view;
	bool camera_updated = true;     // prevent unnecessary transaction and processing
	                                // of the `global_transform' matrix
	float fov;

public:
	Camera(CameraProperties properties);
	~Camera();

	bool Render(Renderer& render);
	bool Destroy(Renderer& render);

	void Attach();
	void Detach();
	void ApplyProperties(CameraProperties properties);
};

}

#endif // SOLARIS_CAMERA_H