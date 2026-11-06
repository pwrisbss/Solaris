#include "Camera.hpp"

namespace Solaris {

Camera::Camera(CameraProperties properties) :
	RenderObject(),
	properties(properties) {
	if (properties.perspective) {
		this->projection = glm::perspective(this->properties.fov, properties.aspect_ratio,
			properties.near_clip, properties.far_clip);
	} else {
		this->projection = glm::ortho(properties.left, properties.right,
			properties.bottom, properties.top, properties.near_clip, properties.far_clip);
	}

	this->view = glm::lookAt(this->properties.position, this->properties.looking_at + this->properties.front_vector,
		this->properties.up_vector);
}

Camera::~Camera() {}

bool Camera::Render(Renderer &render) {
	if (this->camera_updated) {
		render.SetGlobalTransform(this->projection * this->view);
		this->camera_updated = false;
	}

	return true;
}

void Camera::Attach() {
	this->renderable = true;
}

void Camera::Detach() {
	this->renderable = false;
}

void Camera::ApplyProperties(CameraProperties properties) {
	this->properties = properties;

	if (properties.perspective) {
		this->projection = glm::perspective(this->properties.fov, properties.aspect_ratio,
			properties.near_clip, properties.far_clip);
	} else {
		this->projection = glm::ortho(properties.left, properties.right, properties.bottom, properties.top);
	}

	this->view = glm::lookAt(this->properties.position, this->properties.looking_at + this->properties.front_vector,
		this->properties.up_vector);

	this->camera_updated = true;
}

bool Camera::Destroy(Renderer&) {
	return false;
}

glm::vec3 Camera::GetPosition() {
	return this->properties.position;
}

float Camera::GetPitch() {
	return this->properties.pitch;
}

float Camera::GetYaw() {
	return this->properties.yaw;
}

glm::vec3 Camera::GetLookAt() {
	return this->properties.looking_at;
}

void Camera::SetPosition(glm::vec3 to) {
	this->properties.position = to;

	this->view = glm::lookAt(this->properties.position, this->properties.position + this->properties.front_vector,
		this->properties.up_vector);

	this->camera_updated = true;
}

void Camera::SetRotation(float pitch, float yaw) {
	glm::vec3 new_front(1.0f);
	this->properties.pitch = pitch;
	this->properties.yaw = yaw;
	new_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    new_front.y = sin(glm::radians(pitch));
    new_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->properties.front_vector = glm::normalize(new_front);
	this->properties.looking_at = this->properties.front_vector;
	this->properties.right_vector =
		glm::normalize(glm::cross(this->properties.front_vector, this->properties.world_up_vector));
	this->properties.up_vector =
		glm::normalize(glm::cross(this->properties.right_vector, this->properties.front_vector));

	this->view = glm::lookAt(this->properties.position, this->properties.position + this->properties.front_vector,
		this->properties.up_vector);

	this->camera_updated = true;
}

void Camera::SetLookAt(glm::vec3 to) {
	this->properties.looking_at = to;
}

void Camera::Rotate(float pitch, float yaw) {
	this->properties.pitch += glm::radians(pitch);
	this->properties.yaw += glm::radians(yaw);
	this->SetRotation(this->properties.pitch, this->properties.yaw);
}

void Camera::Translate(glm::vec3 by) {
	this->properties.position += by;
	this->SetPosition(this->properties.position);
}

}