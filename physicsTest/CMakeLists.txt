cmake_minimum_required(VERSION 3.0)
project(physicsTest)

# Specify the path to Bullet
set(BULLET_ROOT ${CMAKE_SOURCE_DIR}/../Libraries/bullet3)

# Add Bullet include directories
include_directories(${BULLET_ROOT}/src)

# Link Bullet libraries
link_directories(${BULLET_ROOT}/build/src/BulletDynamics)
link_directories(${BULLET_ROOT}/build/src/BulletCollision)
link_directories(${BULLET_ROOT}/build/src/LinearMath)

# Add the executable
add_executable(physicsTest main.cpp)

# Link the Bullet libraries
target_link_libraries(physicsTest BulletDynamics BulletCollision LinearMath)