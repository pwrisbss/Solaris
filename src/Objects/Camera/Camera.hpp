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
	glm::vec3 right_vector = {1.0f, 0.0f, 0.0f};
	glm::vec3 world_up_vector = this->up_vector;
	glm::vec3 looking_at;
	float pitch = 0.0f;
	float yaw = -90.0f;
	
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
	glm::mat4 projection;
	glm::mat4 view;
	bool camera_updated = true;     // prevent unnecessary transaction and processing
	                                // of the `global_transform' matrix

public:
	CameraProperties properties;
	Camera(CameraProperties properties);
	~Camera();

	bool Render(Renderer& render);
	bool Destroy(Renderer& render);

	void Attach();
	void Detach();
	void ApplyProperties(CameraProperties properties);	// i have no idea why i added this.

	// camera transformation
	glm::vec3 GetPosition();
	glm::vec3 GetLookAt();
	float GetPitch();
	float GetYaw();
	void SetPosition(glm::vec3 to);
	void SetRotation(float pitch, float yaw);
	void SetLookAt(glm::vec3 to);
	void Translate(glm::vec3 by);
	void Rotate(float pitch, float yaw);
};

}

#endif // SOLARIS_CAMERA_H