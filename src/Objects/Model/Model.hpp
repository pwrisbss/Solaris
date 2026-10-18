#ifndef SOLARIS_MODEL_OBJECT_H
#define SOLARIS_MODEL_OBJECT_H

#include <Renderer/RenderObjects.hpp>
#include <Renderer/Renderer.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Solaris {

class Model : public RenderObject {
private:
	glm::vec3 position;
	glm::mat4 model_transform;
	CastedResource<float> mesh_data;
	CastedResource<unsigned char> texture_data;
	bool transform_updated = true;
	unsigned meshVBO;
	unsigned modelVAO;
	unsigned texture;
	unsigned long vertices_count;

public:
	Model(const CastedResource<float>& mesh_data, const CastedResource<unsigned char>& texture_data,
		glm::vec3 initial_pos = {0.0f, 0.0f, 0.0f});
	~Model();

	bool Render(Renderer&);
	bool Construct(Renderer&);
	bool Destroy(Renderer&);

	// getters
	glm::vec3 GetPosition();
	glm::mat4 GetTransform();

	// setters
	void SetPosition(glm::vec3 to);
	void Translate(glm::vec3 by);
};

}

#endif // SOLARIS_MODEL_OBJECT_H