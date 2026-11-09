cmake_minimum_required (VERSION 3.21)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

project(Raytracer)

find_package(Threads REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

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
	"Raytracer/source/Image/JpgWriter.cpp" 
	"Raytracer/include/Image/ImageWriterFactory.h"
	"Raytracer/source/Image/ImageWriterFactory.cpp" 
	"Raytracer/include/Utils/NumericUtils.h" 
	"Raytracer/source/Utils/NumericUtils.cpp" 
	"Raytracer/include/Utils/Log.h" 
	"Raytracer/include/Application/RaytracerWindow.h" 
	"Raytracer/source/Application/RaytracerWindow.cpp" 
	"Raytracer/include/Application/Controller/RaytracerController.h"
	"Raytracer/source/Application/Controller/RaytracerController.cpp"

 "Raytracer/include/Application/RenderPanel.h" "Raytracer/source/Application/RenderPanel.cpp")
	
add_executable(raytracer ${SRCS})

target_include_directories(raytracer
	PRIVATE 
	"${PROJECT_SOURCE_DIR}/Raytracer/include"
	"${PROJECT_SOURCE_DIR}/Libs")

target_link_libraries(raytracer
	PRIVATE Threads::Threads
	PRIVATE Qt6::Widgets
)

if(WIN32)
    set(VCPKG_ROOT_DIR
        "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}"
    )

    add_custom_command(TARGET raytracer POST_BUILD

        # Copier les DLL Qt
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "$<IF:$<CONFIG:Debug>,${VCPKG_ROOT_DIR}/debug/bin,${VCPKG_ROOT_DIR}/bin>"
            "$<TARGET_FILE_DIR:raytracer>"

        # Copier les plugins de plateforme
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "$<IF:$<CONFIG:Debug>,${VCPKG_ROOT_DIR}/debug/Qt6/plugins/platforms,${VCPKG_ROOT_DIR}/Qt6/plugins/platforms>"
            "$<TARGET_FILE_DIR:raytracer>/platforms"

        COMMENT "Deploying Qt dependencies..."
        VERBATIM
    )
endif()



