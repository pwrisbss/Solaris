#include "Model.hpp"

namespace Solaris {

Model::Model(const CastedResource<float>& mesh_data, const CastedResource<unsigned char>& texture_data,
		glm::vec3 initial_pos) : 
	RenderObject(true, false, true, true),
	mesh_data(mesh_data),
	texture_data(texture_data),
	model_transform(1.0f),
	position(initial_pos) {
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
	this->transform_updated = true;
}

}