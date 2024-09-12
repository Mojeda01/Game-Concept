cmake_minimum_required(VERSION 3.10)
project(MetalApp)

set(CMAKE_CXX_STANDARD 14)

find_library(METAL_FRAMEWORK Metal)
find_library(QUARTZCORE_FRAMEWORK QuartzCore)
find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices)
find_library(COCOA_FRAMEWORK Cocoa)  # Add this line to find the Cocoa framework

add_executable(MetalApp main.mm)
target_link_libraries(MetalApp ${METAL_FRAMEWORK} ${QUARTZCORE_FRAMEWORK} ${APPLICATION_SERVICES_FRAMEWORK} ${COCOA_FRAMEWORK})  # Add ${COCOA_FRAMEWORK} here