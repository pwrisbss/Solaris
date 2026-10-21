#ifndef SOLARIS_CAMERA_H
#define SOLARIS_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Renderer/Renderer.hpp>
#include <Renderer/RenderObjects.hpp>

namespace Solaris {

typedef struct CameraProperties {
	glm::vec3 position = {0.0f, 0.0f, 0.0f};
	glm::vec3 up_vector = {0.0f, 1.0f, 0.0f};
	glm::vec3 front_vector = {0.0f, 0.0f, -1.0f};
	glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
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
	glm::vec3 rotation;
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
	void ApplyProperties(CameraProperties properties);	// i have no idea why i added this.

	// camera transformation
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetLookAt();
	void SetPosition(glm::vec3 to);
	void SetRotation(glm::vec3 to);
	void SetLookAt(glm::vec3 to);
	void Translate(glm::vec3 by);
	void Rotate(glm::vec3 by);
};

}

#endif // SOLARIS_CAMERA_H