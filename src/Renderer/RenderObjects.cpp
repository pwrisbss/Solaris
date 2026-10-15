#include "RenderObjects.hpp"
#include "Renderer.hpp"

namespace Solaris {

RenderObject::RenderObject(bool _r, bool _t, bool _c, bool _d) :
	renderable(_r),
	tickable(_t),
	constructible(_c),
	destructible(_d) {}

RenderObject::~RenderObject() {}

bool RenderObject::Construct(Renderer&) { return false; }
bool RenderObject::Destroy(Renderer&) { std::cout << "RenderObject::Destroy() called\n"; return false; }
bool RenderObject::Tick(Renderer&) { return false; }
bool RenderObject::Render(Renderer&) { return false; }

}