#ifndef SOLARIS_UI_H
#define SOLARIS_UI_H

#include "UIObjects.hpp"
#include <Renderer/RenderObjects.hpp>
#include <Shader/Shader.hpp>

namespace Solaris {

class UI;

class UI : public RenderObject {
private:
	std::vector<UIObject*> objects;
	Shader shader;

public:
	UI();
	~UI();

	// render object methods
	bool Construct(Renderer &) NoCall;
	bool Render(Renderer &) NoCall;
	bool Tick(Renderer &) NoCall;
	bool Destroy(Renderer &) NoCall;

	// object methods
	void AttachObject(UIObject * object);
	void DetachObject(UIObject * object);
	bool IsAttached(UIObject * object);

	// UI methods
	void Attach();
	void Detach();

	// debugging
	void Debug_showobjs();
};

}

#endif // SOLARIS_UI_H