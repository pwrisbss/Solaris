#include "Camera.hpp"

namespace Solaris {

Camera::Camera(CameraProperties properties) :
	RenderObject(),
	properties(properties) {
	if (properties.perspective) {
		this->projection = glm::perspective(this->fov, properties.aspect_ratio,
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
		this->projection = glm::perspective(this->fov, properties.aspect_ratio,
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

glm::vec3 Camera::GetRotation() {
	return this->properties.rotation;
}

void Camera::SetPosition(glm::vec3 to) {
	this->properties.position = to;

	this->view = glm::lookAt(this->properties.position, this->properties.looking_at + this->properties.front_vector,
		this->properties.up_vector);

	this->camera_updated = true;
}

void Camera::SetRotation(glm::vec3 by) {
	this->camera_updated = true;
}

}