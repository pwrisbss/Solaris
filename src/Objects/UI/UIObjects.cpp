#include "UIObjects.hpp"

namespace Solaris {

UIObject::UIObject(Rectangle rect, CastedResource<unsigned char> texture) :
	texture(texture),
	rect(rect) {}

UIObject::UIObject(float x, float y, float width, float height, CastedResource<unsigned char> texture) :
	texture(texture),
	rect({ x, y, width, height }) {}

UIObject::UIObject() {}
UIObject::~UIObject() {}

void UIObject::SetRect(Rectangle rect) {
	this->rect = rect;
}

void UIObject::SetRect(float x, float y, float width, float height) {
	this->rect = { x, y, width, height };
}

void UIObject::SetTexture(CastedResource<unsigned char> texture) {
	this->texture = texture;
}

CastedResource<unsigned char> UIObject::GetTexture() {
	return this->texture;
}

Rectangle UIObject::GetRect() {
	return this->rect;
}

}