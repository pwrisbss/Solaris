#include "UI.hpp"

namespace Solaris {

const char * UIVertexShader = R"(
#version 330 core

layout (location = 0) in vec2 vertexPos;
layout (location = 1) in int vertexLayer;

void main() {
	gl_Position = vec4(vertexPos.xy, vertexLayer, 1.0f);
}
)";

const char * UIFragmentShader = R"(
#version 330 core

out vec4 fragCol;

void main() {
	fragCol = vec4(1.0f, 1.0f, 1.0f, 1.0f);	// TODO temporary
}

)";

UI::UI() :
	RenderObject(true, true, true, true),
	shader(UIVertexShader, UIFragmentShader) {}

UI::~UI() {}

void UI::AttachObject(UIObject *object) {
	this->objects.push_back(object);
}

void UI::DetachObject(UIObject *object) {
	for (unsigned i = 0; i < this->objects.size(); i++) {
		if (this->objects[i] == object) this->objects.erase(this->objects.begin() + i);
	}
}

bool UI::IsAttached(UIObject *object) {
	for (auto& e : this->objects) {
		if (e == object) return true;
	}

	return false;
}

void UI::Debug_showobjs() {
	std::cout << "UI attached objects: {\n";
	for (auto& e : this->objects) {
		std::cout << "\t" << e << ",\n";
	}
	std::cout << "}\n\n";
}

}