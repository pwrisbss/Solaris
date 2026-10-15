target_sources(${PROJECT_NAME}
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			.
		FILES
			Shader/Shader.hpp
			ShortNamespace.hpp
			Renderer/Renderer.hpp
			Renderer/RenderObjects.hpp
			ResourceMan/ResourceMan.hpp
)