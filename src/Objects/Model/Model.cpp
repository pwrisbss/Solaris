#include "Model.hpp"

namespace Solaris {

Model::Model(const CastedResource<float>& mesh_data, const CastedResource<unsigned char>& texture_data,
		glm::vec3 initial_pos) : 
	RenderObject(true, false, true, true),
	mesh_data(mesh_data),
	texture_data(texture_data),
	model_transform(1.0f),
	position(initial_pos),
	scale(1.0f),
	rotx(0), roty(0), rotz(0) {
	model_transform = glm::translate(model_transform, this->position);
}

bool Model::Construct(Renderer&) {
	glGenVertexArrays(1, &this->modelVAO);
	glBindVertexArray(this->modelVAO);

	glGenBuffers(1, &this->meshVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->meshVBO);
	glBufferData(GL_ARRAY_BUFFER, this->mesh_data.len * sizeof(float), this->mesh_data.pdata, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// TODO add texture stuff

	this->vertices_count = this->mesh_data.len / 3;

	// TODO add error handling
	// when mesh_data.len isnt divisible
	// by 3
	
	return true;
}

bool Model::Render(Renderer& renderer) {
	auto shader = renderer.GetShaderPtr();
	shader->Use();

	// send transform data
	if (this->transform_updated) {
		unsigned program = shader->GetShaderProg();
		unsigned transform_loc = glGetUniformLocation(program, "model_transform");
		glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(this->model_transform));

		this->transform_updated = false;
	}

	glBindVertexArray(this->modelVAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices_count);

	return true;
}

bool Model::Destroy(Renderer&) {
	std::cout << "Model::Destroy() called\n";

	glDeleteBuffers(1, &this->meshVBO);
	glDeleteVertexArrays(1, &this->modelVAO);

	return true;
}

Model::~Model() {};

// getters
glm::vec3 Model::GetPosition() {
	return this->position;
}

glm::mat4 Model::GetTransform() {
	return this->model_transform;
}

// setters
void Model::SetPosition(glm::vec3 to) {
	this->position = to;
	this->model_transform = glm::translate(glm::mat4(1.0f), this->position);

	// re-apply previous transformations
	this->model_transform = glm::rotate(this->model_transform, this->rotx, XAxis);
	this->model_transform = glm::rotate(this->model_transform, this->roty, YAxis);
	this->model_transform = glm::rotate(this->model_transform, this->rotz, ZAxis);
	this->model_transform = glm::scale(this->model_transform, this->scale);

	this->transform_updated = true;
}

void Model::SetRotation(float x, float y, float z) {
	this->rotx = x;
	this->roty = y;
	this->rotz = z;
	this->model_transform = glm::rotate(glm::mat4(1.0f), this->rotx, XAxis);
	this->model_transform = glm::rotate(glm::mat4(1.0f), this->roty, YAxis);
	this->model_transform = glm::rotate(glm::mat4(1.0f), this->rotz, ZAxis);

	// re-apply previous transformations
	this->model_transform = glm::translate(this->model_transform, this->position);
	this->model_transform = glm::scale(this->model_transform, this->scale);

	this->transform_updated = true;
}

void Model::SetScale(glm::vec3 to) {
	this->scale = to;
	this->model_transform = glm::scale(glm::mat4(1.0f), this->scale);

	// re-apply previous transformations
	this->model_transform = glm::rotate(this->model_transform, this->rotx, XAxis);
	this->model_transform = glm::rotate(this->model_transform, this->roty, YAxis);
	this->model_transform = glm::rotate(this->model_transform, this->rotz, ZAxis);
	this->model_transform = glm::translate(this->model_transform, this->position);

	this->transform_updated = true;
}

void Model::Translate(glm::vec3 by) {
	this->position += by;
	this->model_transform = glm::translate(this->model_transform, by);
	this->transform_updated = true;
}

void Model::Rotate(float x, float y, float z) {
	this->rotx += x;
	this->roty += y;
	this->rotz += z;
	this->model_transform = glm::rotate(this->model_transform, x, XAxis);
	this->model_transform = glm::rotate(this->model_transform, y, YAxis);
	this->model_transform = glm::rotate(this->model_transform, z, ZAxis);
	this->transform_updated = true;
}

void Model::Rotate(float value, glm::vec3 axis) {
	if (axis == XAxis) {
		this->rotx += value;
	} else if (axis == YAxis) {
		this->roty += value;
	} else if (axis == ZAxis) {
		this->rotz += value;
	} else {
		std::cout << "W: Rotating in an unknown axis! Expect unpredicted behavior.\n";
	}

	this->model_transform = glm::rotate(this->model_transform, value, axis);
	this->transform_updated = true;
}

void Model::Scale(glm::vec3 by) {
	this->scale *= by;
	this->model_transform = glm::scale(this->model_transform, by);
	this->transform_updated = true;
}

glm::vec3 Model::GetScale() {
	return this->scale;
}

float Model::GetXRotation() {
	return this->rotx;
}

float Model::GetYRotation() {
	return this->roty;
}

float Model::GetZRotation() {
	return this->rotz;
}

}