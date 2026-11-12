#ifndef SOLARIS_MODEL_OBJECT_H
#define SOLARIS_MODEL_OBJECT_H

#include <Renderer/RenderObjects.hpp>
#include <Renderer/Renderer.hpp>
#include <Texture/Texture.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Solaris {

constexpr glm::vec3 XAxis(1.0f, 0.0f, 0.0f);
constexpr glm::vec3 YAxis(0.0f, 1.0f, 0.0f);
constexpr glm::vec3 ZAxis(0.0f, 0.0f, 1.0f);

class Model : public RenderObject { MyNameIs("Model")
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::mat4 model_transform;
	CastedResource<float> mesh_data;
	Texture texture;
	bool transform_updated = true;
	float rotx;
	float roty;
	float rotz;
	unsigned meshVBO;
	unsigned modelVAO;
	unsigned textureID;
	unsigned long vertices_count;

public:
	Model(const CastedResource<float>& mesh_data, Texture texture_data,
		glm::vec3 initial_pos = {0.0f, 0.0f, 0.0f});
	~Model();

	bool Render(Renderer&) override;
	bool Tick(Renderer&) override NoCall;
	bool Construct(Renderer&) override;
	bool Destroy(Renderer&) override;

	// getters
	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::mat4 GetTransform();
	float GetXRotation();
	float GetYRotation();
	float GetZRotation();

	// setters
	void SetPosition(glm::vec3 to);
	void SetScale(glm::vec3 to);
	void SetRotation(float x, float y, float z);
	void SetXRotation(float to);
	void SetYRotation(float to);
	void SetZRotation(float to);

	void Translate(glm::vec3 by);
	void Scale(glm::vec3 by);
	void Rotate(float value, glm::vec3 axis);
	void Rotate(float x, float y, float z);
};

}

#endif // SOLARIS_MODEL_OBJECT_H