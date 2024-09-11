cmake_minimum_required(VERSION 3.10)
project(NewOpenGLProject)

set(CMAKE_CXX_STANDARD 11)

# Add paths to GLEW, GLFW, and GLM
set(GLEW_INCLUDE_DIRS "/opt/homebrew/opt/glew/include")
set(GLFW_INCLUDE_DIRS "/opt/homebrew/opt/glfw/include")
set(GLM_INCLUDE_DIRS "/opt/homebrew/include")
set(GLEW_LIBRARIES "/opt/homebrew/opt/glew/lib/libGLEW.dylib")
set(GLFW_LIBRARIES "/opt/homebrew/opt/glfw/lib/libglfw.dylib")

include_directories(${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)

add_executable(NewOpenGLProject main.cpp)
target_link_libraries(NewOpenGLProject ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})