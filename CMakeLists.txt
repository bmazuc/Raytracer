cmake_minimum_required (VERSION 3.8)

project(Raytracer)

set(SRCS
	main.cpp
	"include/Renderer.h" 
	"source/Renderer.cpp"
	"include/Maths/Vec3.h"
	"source/Maths/Vec3.cpp"
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
	"include/Hittable.h" 
	"source/Hittable.cpp" 
	"include/Scene.h" 
	"source/Scene.cpp" 
	"include/Maths/Maths.h" 
	"include/Maths/Interval.h" 
	"source/Maths/Interval.cpp" 
	"include/ExampleScene.h" 
	"source/ExampleScene.cpp" 
	"include/Material/Material.h" 
	"include/Material/Lambertian.h" 
	"source/Material/Lambertian.cpp" 
	"include/Material/Metal.h" 
	"source/Material/Metal.cpp" 
	"include/Material/Dielectric.h" 
	"source/Material/Dielectric.cpp")
	
add_executable(raytracer ${SRCS})

target_include_directories(raytracer
	PRIVATE "${PROJECT_SOURCE_DIR}/include")