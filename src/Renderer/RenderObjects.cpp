#include "RenderObjects.hpp"
#include "Renderer.hpp"

namespace Solaris {

RenderObject::RenderObject(bool _r, bool _t, bool _c, bool _d) :
	renderable(_r),
	tickable(_t),
	constructible(_c),
	destructible(_d) {}

bool RenderObject::Construct(Renderer&) { return false; }
bool RenderObject::Destroy(Renderer&) { return false; }
bool RenderObject::Tick(Renderer&) { return false; }
bool RenderObject::Render(Renderer&) { return false; }
std::string RenderObject::WhatsYourName() { return "RenderObject"; }

}