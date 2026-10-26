cmake_minimum_required (VERSION 3.8)

project(Raytracer)

set(SRCS
	main.cpp
	"include/Raytracer.h" 
	"source/Raytracer.cpp"
	"include/Vec3.h"
	"source/Vec3.cpp"
	"include/Color.h"
	"source/Color.cpp"
	"include/Ray.h" 
	"source/Ray.cpp" 
	"include/Camera.h" 
	"source/Camera.cpp" 
	"include/Viewport.h" 
	"source/Viewport.cpp" 
	"include/Sphere.h" 
	"source/Sphere.cpp"
)
	
add_executable(raytracer ${SRCS})

target_include_directories(raytracer
	PRIVATE "${PROJECT_SOURCE_DIR}/include")