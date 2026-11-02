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
	"include/Scene/Sphere.h" 
	"source/Scene/Sphere.cpp"
	"include/Scene/Hittable.h" 
	"source/Scene/Hittable.cpp" 
	"include/Scene/Scene.h" 
	"source/Scene/Scene.cpp" 
	"include/Maths/Maths.h" 
	"include/Maths/Interval.h" 
	"source/Maths/Interval.cpp"  
	"include/Material/Material.h" 
	"include/Material/Lambertian.h" 
	"source/Material/Lambertian.cpp" 
	"include/Material/Metal.h" 
	"source/Material/Metal.cpp" 
	"include/Material/Dielectric.h" 
	"source/Material/Dielectric.cpp" 
	"include/Scene/Sky/Sky.h" 
	"include/Scene/Sky/GradientSky.h" 
	"source/Scene/Sky/GradientSky.cpp" "include/PPMWriter.h" "source/PPMWriter.cpp")
	
add_executable(raytracer ${SRCS})

target_include_directories(raytracer
	PRIVATE "${PROJECT_SOURCE_DIR}/include")