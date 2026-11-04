cmake_minimum_required (VERSION 3.8)

project(Raytracer)

find_package(Threads REQUIRED)

set(SRCS
	main.cpp
	"Raytracer/include/Renderer.h" 
	"Raytracer/source/Renderer.cpp"
	"Raytracer/include/Maths/Vec3.h"
	"Raytracer/source/Maths/Vec3.cpp"
	"Raytracer/include/Color.h"
	"Raytracer/source/Color.cpp"
	"Raytracer/include/Ray.h" 
	"Raytracer/source/Ray.cpp" 
	"Raytracer/include/Camera.h" 
	"Raytracer/source/Camera.cpp" 
	"Raytracer/include/Viewport.h" 
	"Raytracer/source/Viewport.cpp" 
	"Raytracer/include/Scene/Sphere.h" 
	"Raytracer/source/Scene/Sphere.cpp"
	"Raytracer/include/Scene/Hittable.h" 
	"Raytracer/source/Scene/Hittable.cpp" 
	"Raytracer/include/Scene/Scene.h" 
	"Raytracer/source/Scene/Scene.cpp" 
	"Raytracer/include/Maths/Maths.h" 
	"Raytracer/include/Maths/Interval.h" 
	"Raytracer/source/Maths/Interval.cpp"  
	"Raytracer/include/Material/Material.h" 
	"Raytracer/include/Material/Lambertian.h" 
	"Raytracer/source/Material/Lambertian.cpp" 
	"Raytracer/include/Material/Metal.h" 
	"Raytracer/source/Material/Metal.cpp" 
	"Raytracer/include/Material/Dielectric.h" 
	"Raytracer/source/Material/Dielectric.cpp" 
	"Raytracer/include/Scene/Sky/Sky.h" 
	"Raytracer/include/Scene/Sky/GradientSky.h" 
	"Raytracer/source/Scene/Sky/GradientSky.cpp" 
	"Raytracer/include/Image/PPMWriter.h" 
	"Raytracer/source/Image/PPMWriter.cpp" 
	"Raytracer/include/Raytracer.h" 
	"Raytracer/source/Raytracer.cpp" 
	"Raytracer/include/ExampleScenes/BasicScene.h" 
	"Raytracer/include/ExampleScenes/ComplexScene.h" 
	"Raytracer/include/Image/ImageBuffer.h" 
	"Raytracer/source/Image/ImageBuffer.cpp" 
	"Raytracer/include/ThreadPool.h" 
	"Raytracer/source/ThreadPool.cpp" 
	"Raytracer/include/Tile.h"
	"Raytracer/include/Image/ImageWriter.h"
	"Raytracer/include/Image/PngWriter.h"
	"Raytracer/source/Image/PngWriter.cpp"
	"Libs/stb/stb_image_write.h" 
	"Raytracer/include/Image/JpgWriter.h" 
	"Raytracer/source/Image/JpgWriter.cpp")
	
add_executable(raytracer ${SRCS})

if(MSVC)
    target_compile_definitions(raytracer PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

target_include_directories(raytracer
	PRIVATE 
	"${PROJECT_SOURCE_DIR}/Raytracer/include"
	"${PROJECT_SOURCE_DIR}/Libs")

target_link_libraries(raytracer
	PRIVATE Threads::Threads
)