cmake_minimum_required(VERSION 3.23)
project(VSEchelon)

set(CMAKE_CXX_FLAGS "-O2")

# The Echelon Library
add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include/
)

target_link_libraries(${PROJECT_NAME} glfw3 GL X11 pthread Xi Xrandr dl)

# Debugging
if(CXX_DEBUG)
	set(CMAKE_CXX_FLAGS "-g")
endif(CXX_DEBUG)

# Echelon Components
add_subdirectory(src/Shader)
add_subdirectory(src/Renderer)
add_subdirectory(src/ResourceMan)
add_subdirectory(src/Objects/Camera)
add_subdirectory(src/Objects/Model)
add_subdirectory(src/)

# Tests
if(BUILD_TESTS)
	add_subdirectory(tests/)
endif(BUILD_TESTS)
