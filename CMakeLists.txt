cmake_minimum_required (VERSION 3.8)

project(Raytracer)

set(SRCS
	main.cpp
	"include/Image.h" 
	"source/Image.cpp"
)
	
add_executable(raytracer ${SRCS})

target_include_directories(raytracer
	PRIVATE "${PROJECT_SOURCE_DIR}/include")