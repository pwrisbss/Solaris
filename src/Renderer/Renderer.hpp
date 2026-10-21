#ifndef SOLARIS_RENDERER_H
#define SOLARIS_RENDERER_H

/**
 * @file Renderer.hpp
 * @author pwr (pwrisbss@tuta.io)
 * @brief Solaris Renderer C++ header
 * @version alpha-0.0
 * @date 2026-10-15
 * 
 * @copyright GNU General Public License (see COPYING)
 * 
 */
 
/**
  * @page renderer The Solaris Renderer
  * @todo document `Renderer`
  * 
  */

/**
 * @mainpage The Solaris Game Engine
 *
 * Voidstar's Solaris is a multi-platform open-source game engine written in C++ based on OpenGL. This documentation will
 * provide all the necessary information you will need to have in order to work with Solaris.
 *
 * @warning Solaris, along with this documentation, is still in its alpha phase. Don't expect it to be bullet-proof, or
 * complete and ready for usage.
 *
 * @remark Feel free to contribute to this project at https://github.com/pwrisbss/Solaris/
 */

#include <iostream>
#include <functional>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Shader/Shader.hpp>
#include "RenderObjects.hpp"

namespace Solaris {

class Renderer;

typedef std::function<bool(Renderer&)> RendererTickEvent;

/**
 * @class Renderer
 * @brief Solaris Renderer class
 *
 * @details Almost all interactions with OpenGL will be done through this class. A sort of an OpenGL
 * wrapper, if you will.
 * 
 */
class Renderer {
private:
	std::vector<RendererTickEvent> events;
	std::vector<RenderObject*> objects;
	glm::mat4 global_transform;	// sends this as `uniform mat4 global_transform' to the active shader
	Shader * shader;
	GLFWwindow * window;

public:
	/**
	 * @fn Renderer::Renderer(std::string window_title, int window_width, int window_height)
	 * @brief Construct a new Renderer object
	 * @details This will also initialize GLFW and GLAD and construct a new window, hence its ideal
	 * for each program to have one renderer and one renderer only.
	 * 
	 * @param window_title Title of the created window
	 * @param window_width Width of the created window
	 * @param window_height Height of the created window
	 */
	Renderer(std::string window_title, int window_width, int window_height);

	/**
	 * @fn Renderer::Renderer(std::string window_title, int window_width, int window_height, Shader& shader)
	 * @brief Construct a new Renderer object
	 * @details Same as Renderer::Renderer(std::string window_title, int window_width, int window_height),
	 * except also attaches a shader on constuction
	 * 
	 * 
	 * @param window_title Title of the created window
	 * @param window_width Width of the created window
	 * @param window_height Height of the created window
	 * @param shader Shader to be attached on construction
	 */
	Renderer(std::string window_title, int window_width, int window_height, Shader& shader);
	~Renderer();

	/**
	 * @fn void Tick()
	 * @brief Renderer Tick (see @ref renderer)
	 * 
	 */
	void Tick();

	/**
	 * @fn void AddTickEvent(RendererTickEvent event_func)
	 * @brief Adds a tick event. That is, a function of type RendererTickEvent that will be executed on
	 * each renderer tick (see @ref renderer).
	 * 
	 * @param event_func Event function to attach
	 */
	void AddTickEvent(RendererTickEvent event_func);

	// getters
	/**
	 * @fn bool GetShouldClose()
	 * @brief Returns `true` if the user has tried to close the window, `false` otherwise.
	 * 
	 * @return true User has asked to close the program.
	 */
	bool GetShouldClose();

	/**
	 * @fn GLFWwindow * GetGLFWWindow()
	 * @brief Get the pointer to the GLFW window of this renderer.
	 * 
	 * @return GLFWwindow* Pointer to the GLFW window
	 */
	GLFWwindow * GetGLFWWindow();

	/**
	 * @fn Shader * GetShaderPtr()
	 * @brief Get the pointer to the attached Shader object
	 * 
	 * @return Shader* Pointer to the currently attached shader.
	 */
	Shader * GetShaderPtr();

	// setters
	/**
	 * @fn void SetShouldClose(bool value)
	 * @brief Set if the window should close.
	 * 
	 * @param value Should the window close?
	 */
	void SetShouldClose(bool value);

	/**
	 * @fn void SetGlobalTransform(glm::mat4 set_to)
	 * @brief Set the `mat4 global_transform` uniform on the shader pipeline (see @ref renderer).
	 * 
	 * @param set_to The transform matrix `global_transform` will be set to.
	 */
	void SetGlobalTransform(glm::mat4 set_to);

	/**
	 * @fn void AttachShader(Shader& shader)
	 * @brief Attach a new shader to the current renderer.
	 *
	 * @note Please note that when attaching a shader to a renderer, the attached shader
	 * will be copied to a new location. Hence its a good idea to discard of the shader after
	 * it has been attached, unless you plan on using it elsewhere later.
	 * @bug When attaching a shader to a renderer with an already attached shader, the previous shader
	 * won't be deallocated on the memory.
	 * 
	 * @param shader Shader object to be attached.
	 */
	void AttachShader(Shader& shader);

	/**
	 * @fn void AttachRenderObject(RenderObject * object)
	 * @brief 
	 * 
	 * @param object RenderObject to be attached
	 * @see @ref renderobject
	 */
	void AttachRenderObject(RenderObject * object);
};

}

#endif // SOLARIS_RENDERER_H
