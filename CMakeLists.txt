cmake_minimum_required (VERSION 3.8)

project(Raytracer)

set(SRCS
	main.cpp
	"include/Image.h" 
	"source/Image.cpp"
	"include/Vec3.h"
	"source/Vec3.cpp"
	"include/Color.h"
	"source/Color.cpp"
)
	
add_executable(raytracer ${SRCS})

target_include_directories(raytracer
	PRIVATE "${PROJECT_SOURCE_DIR}/include")