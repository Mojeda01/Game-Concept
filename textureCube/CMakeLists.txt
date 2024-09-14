cmake_minimum_required(VERSION 3.10)
project(TextureCube)

set(CMAKE_CXX_STANDARD 14)

# Add paths to GLEW, GLFW, and GLM
set(GLEW_INCLUDE_DIRS "/opt/homebrew/opt/glew/include")
set(GLFW_INCLUDE_DIRS "/opt/homebrew/opt/glfw/include")
set(GLM_INCLUDE_DIRS "/opt/homebrew/include")
set(GLEW_LIBRARIES "/opt/homebrew/opt/glew/lib/libGLEW.dylib")
set(GLFW_LIBRARIES "/opt/homebrew/opt/glfw/lib/libglfw.dylib")

include_directories(${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)

# Specify the source files
set(SOURCES
    main.cpp
    text_renderer.cpp
    stb_image_impl.cpp  # Add this line
)

# Check if each source file exists
foreach(SOURCE ${SOURCES})
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE})
        message(FATAL_ERROR "Source file '${SOURCE}' not found!")
    endif()
endforeach()

# Add executable
add_executable(TextureCube ${SOURCES})

# Link libraries
target_link_libraries(TextureCube
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
)

# Copy textures to build directory
file(COPY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR})