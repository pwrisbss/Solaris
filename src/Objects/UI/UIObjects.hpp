#ifndef SOLARIS_UIOBJECT_H
#define SOLARIS_UIOBJECT_H

#include <Objects/Model/Model.hpp>
#include <ResourceMan/ResourceMan.hpp>

namespace Solaris {

class UIObject;
typedef struct Rectangle {
	float x;
	float y;
	float width;
	float height;
	bool is_null = false;
} Rectangle;

const Rectangle NoRect = { .is_null = true };

class UIObject {
private:
	Rectangle rect = NoRect;
	CastedResource<unsigned char> texture = NoTexture;

public:
	UIObject();
	UIObject(Rectangle rect, CastedResource<unsigned char> texture = NoTexture);
	UIObject(float x, float y, float width, float height, CastedResource<unsigned char> texture = NoTexture);
	~UIObject();

	CastedResource<unsigned char> GetTexture();
	Rectangle GetRect();

	void SetTexture(CastedResource<unsigned char> texture);
	void SetRect(Rectangle rect);
	void SetRect(float x, float y, float width, float height);
};

}

#endif // SOLARIS_UIOBJECT_H