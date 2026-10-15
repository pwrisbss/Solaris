/**
 * @file RenderObjects.hpp
 * @author pwr (pwrisbss@tuta.io)
 * @brief RenderObject class declaration
 * @version alpha-0.0
 * @date 2026-10-15
 * @copyright GNU General Public License (see COPYING)
 * 
 */

#ifndef SOLARIS_RENDEREROBJECTS_H
#define SOLARIS_RENDEREROBJECTS_H

#include <ResourceMan/ResourceMan.hpp>
#include <functional>

namespace Solaris {

class Renderer;

/**
 * @page renderobject Render Objects
 *
 * A Render Object is any object of any type derived from the `Solaris::RenderObject` base class.
 *
 * @section renderobject-definition Defining Render Objects
 * @subsection renderobject-definition-polymorphism Polymorphism
 * A Render Object is defined as an object that can be pointed to by a `Solaris::RenderObject*`.
 * Basically, what this means is that any object of any class that derives from `Solaris::RenderObject`,
 * along with `Solaris::RenderObject` itself, could be considered a Render Object.
 * 
 * Consider the following examples:
 * @code {.cpp}
 * // NOT Render Objects
 * int x;
 * Solaris::Resource resource1;
 * 
 * class SomeClass;
 * SomeClass y;
 *
 * // Render Objects
 * Solaris::Model sample_model;
 * Solaris::Camera sample_camera;
 * Solaris::RenderObject sample_object;   // although serves no valuable purpose (the reason will be clarified later),
 *                                        // technically it is indeed a render object
 * 
 * class Foo : public Solaris::RenderObject;
 * Foo sample_foo;
 * @endcode
 * 
 * @subsection renderobject-definition-siblings Relationship with Siblings
 *
 * Along with the aforementioned requirement, a render object must have at least one state/configuration
 * which allows all of its siblings (render objects attached to the same renderer, see @ref renderer)
 * to function normally even when itself is present.
 *
 * In other words, consider a render object type such as `Solaris::Model`. Its possible configurations
 * are all the mesh and texture resources (`Solaris::Resource`), positions, rotations, etc. it can contain.
 * Normally, every model configured in a certain way could be siblings with all the other models configured
 * in different ways, without causing any of them to render improperly.
 *
 * Alternatively, consider a render object type such as `Solaris::Camera`. Its possible configurations are the different
 * possible positions, projections, etc. it can have (plus an enabled/disabled state). While an enabled `Camera` object
 * would cause problems if siblings with other enabled `Camera` object(s), in its disabled configurations, it doesn't
 * cause any problems with rendering or any other events (unless its somehow misconfigured otherwise).
 *
 */

/**
 * @brief Render Object abstract class.
 *
 * @details Base abstract class for all render object classes. See @ref renderobject
 * 
 */
class RenderObject {
public:
	RenderObject(bool _r = false, bool _t = false, bool _c = false, bool _d = false);
	~RenderObject();

	bool renderable;
	bool tickable;
	bool constructible;
	bool destructible;

	virtual bool Render(Renderer&);
	virtual bool Tick(Renderer&);
	virtual bool Construct(Renderer&);
	virtual bool Destroy(Renderer&);
};

}

#endif // SOLARIS_RENDEREROBJECTS_H
