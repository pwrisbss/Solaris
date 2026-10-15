// Renderer Tick Events are functions that are called each renderer tick, accepting a
// reference to the calling renderer as their only argument.

#include "Renderer.hpp"

namespace Solaris {

void Renderer::AddTickEvent(RendererTickEvent event_func) {
	this->events.push_back(event_func);
}

}