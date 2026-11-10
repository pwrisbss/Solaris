cmake_minimum_required(VERSION 3.23)
project(Solaris)

option(BUILD_TESTS "Build test binaries" NO)
option(CXX_DEBUG "Enable the debug flag (-g) for compiler" NO)
option(NO_OPTIMIZE "Disable optimization flag (-O2) while compiling" NO)

# The Solaris Library
add_library(${PROJECT_NAME})

if(NOT NO_OPTIMIZE)
	target_compile_options(${PROJECT_NAME} PRIVATE -O2)
endif(NOT NO_OPTIMIZE)

target_sources(${PROJECT_NAME}
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include/
)

target_link_libraries(${PROJECT_NAME} glfw3 GL)

if(UNIX)
	target_link_libraries(${PROJECT_NAME} X11 pthread Xi Xrandr dl)
endif(UNIX)

# Debugging
if(CXX_DEBUG)
	target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif(CXX_DEBUG)

# Solaris Components
add_subdirectory(src/Shader)
add_subdirectory(src/Renderer)
add_subdirectory(src/ResourceMan)
add_subdirectory(src/Objects/Camera)
add_subdirectory(src/Objects/Model)
add_subdirectory(src/Objects/UI)
add_subdirectory(src/Texture)
add_subdirectory(src/)

# Tests
if(BUILD_TESTS)
	add_subdirectory(tests/)
endif(BUILD_TESTS)
