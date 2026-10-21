#include "Camera.hpp"

namespace Solaris {

Camera::Camera(CameraProperties properties) :
	RenderObject(),
	position(properties.position),
	up(properties.up_vector),
	cam_front(properties.front_vector),
	fov(properties.fov) {
	if (properties.perspective) {
		this->projection = glm::perspective(this->fov, properties.aspect_ratio,
			properties.near_clip, properties.far_clip);
	} else {
		this->projection = glm::ortho(properties.left, properties.right,
			properties.bottom, properties.top, properties.near_clip, properties.far_clip);
	}

	this->view = glm::lookAt(this->position, this->looking_at + this->cam_front, this->up);
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
	this->position = properties.position;
	this->up = properties.up_vector;
	this->cam_front = properties.front_vector;
	this->fov = properties.fov;
	this->looking_at = properties.looking_at;

	if (properties.perspective) {
		this->projection = glm::perspective(this->fov, properties.aspect_ratio,
			properties.near_clip, properties.far_clip);
	} else {
		this->projection = glm::ortho(properties.left, properties.right, properties.bottom, properties.top);
	}

	this->view = glm::lookAt(this->position, this->looking_at + this->cam_front, this->up);

	this->camera_updated = true;
}

bool Camera::Destroy(Renderer&) {
	return false;
}

glm::vec3 Camera::GetPosition() {
	return this->position;
}

glm::vec3 Camera::GetRotation() {
	return this->rotation;
}

void Camera::SetPosition(glm::vec3 to) {
	this->position = to;

	this->view = glm::lookAt(this->position, this->looking_at + this->cam_front, this->up);

	this->camera_updated = true;
}

void Camera::SetRotation(glm::vec3 to) {
	this->rotation = to;
	this->camera_updated = true;
}

}