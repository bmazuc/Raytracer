#include "Renderer.h"
#include "Camera.h"
#include "Scene/Scene.h"
#include "Scene/Sky/GradientSky.h"
#include "Scene/Sphere.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"
#include "Color.h"
#include "Maths/Maths.h"
#include "PPMWriter.h"

void RenderBasicScene(const Renderer& renderer)
{
    CameraConfiguration cameraConfig;
    cameraConfig.imageWidth = 400;
    cameraConfig.aspectRatio = 16.0f / 9.0f;
    cameraConfig.samplesPerPixel = 100;
    cameraConfig.maxDepth = 50;

    cameraConfig.fov = 20;
    cameraConfig.position = Vec3(-2.0f, 2.0f, 1.0f);
    cameraConfig.lookAt = Vec3(0.0f, 0.0f, -1.0f);
    cameraConfig.vUp = Vec3(0.0f, 1.0f, 0.0f);

    cameraConfig.defocusAngle = 0.0f;
    cameraConfig.focusDistance = 10.0f;

    Camera* camera = new Camera(cameraConfig);

    Scene* scene = new Scene();

    GradientSky* sky = new GradientSky(Color(1.0f, 1.0f, 1.0f), Color(0.5f, 0.7f, 1.0f));
    scene->SetSky(sky);

    std::shared_ptr<Lambertian> materialGround = std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
    std::shared_ptr<Lambertian> materialCenter = std::make_shared<Lambertian>(Color(0.1f, 0.2f, 0.5f));
    std::shared_ptr<Dielectric> materialLeft = std::make_shared<Dielectric>(1.50f);
    std::shared_ptr<Dielectric> materialBubble = std::make_shared<Dielectric>(1.00f / 1.50f);
    std::shared_ptr<Metal> materialRight = std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f), 1.0f);

    scene->Add(std::make_shared<Sphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f, materialGround));
    scene->Add(std::make_shared<Sphere>(Vec3(0.0f, 0.0f, -1.2f), 0.5f, materialCenter));
    scene->Add(std::make_shared<Sphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, materialLeft));
    scene->Add(std::make_shared<Sphere>(Vec3(-1.0f, 0.0f, -1.0f), 0.4f, materialBubble));
    scene->Add(std::make_shared<Sphere>(Vec3(1.0f, 0.0f, -1.0f), 0.5f, materialRight));

    PPMWriter* writer = new PPMWriter(std::cout);

    renderer.Render(*camera, *scene, *writer);

    delete writer;
    writer = nullptr;

    delete scene;
    scene = nullptr;

    delete camera;
    camera = nullptr;
}

void RenderComplexScene(const Renderer& renderer)
{
	CameraConfiguration cameraConfig;
	cameraConfig.imageWidth = 1200;
	cameraConfig.aspectRatio = 16.0f / 9.0f;
	cameraConfig.samplesPerPixel = 500;
	cameraConfig.maxDepth = 50;

	cameraConfig.fov = 20;
	cameraConfig.position = Vec3(13.0f, 2.0f, 3.0f);
	cameraConfig.lookAt = Vec3(0.0f, 0.0f, 0.0f);
	cameraConfig.vUp = Vec3(0.0f, 1.0f, 0.0f);

	cameraConfig.defocusAngle = 0.6f;
	cameraConfig.focusDistance = 10.0f;

	Camera* camera = new Camera(cameraConfig);

	Scene* scene = new Scene();
	
    GradientSky* sky = new GradientSky(Color(1.0f, 1.0f, 1.0f), Color(0.5f, 0.7f, 1.0f));
    scene->SetSky(sky);

    std::shared_ptr<Lambertian> materialGround = std::make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
    scene->Add(std::make_shared<Sphere>(Vec3(0.0f, -1000.0f, -1.0f), 1000.f, materialGround));

    for (int a = -11; a < 11; ++a)
    {
        for (int b = -11; b < 11; ++b)
        {
            float chooseMat = maths::Random();
            Vec3 position(a + 0.9f * maths::Random(), 0.2f, b + 0.9f * maths::Random());

            if ((position - Vec3(4.0f, 0.2f, 0.0f)).Length() > 0.9)
            {
                std::shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.8)
                {
                    // diffuse
                    Color albedo = Color::Random() * Color::Random();
                    sphereMaterial = std::make_shared<Lambertian>(albedo);

                }
                else if (chooseMat < 0.95)
                {
                    // metal
                    auto albedo = Color::Random(0.5f, 1.0f);
                    float roughness = maths::Random(0.0f, 0.5f);
                    sphereMaterial = std::make_shared<Metal>(albedo, roughness);
                }
                else
                {
                    // glass
                    sphereMaterial = std::make_shared<Dielectric>(1.5f);
                }

                scene->Add(std::make_shared<Sphere>(position, 0.2f, sphereMaterial));
            }
        }
    }

    std::shared_ptr<Dielectric> material1 = std::make_shared<Dielectric>(1.5f);
    scene->Add(std::make_shared<Sphere>(Vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));

    std::shared_ptr<Lambertian> material2 = std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    scene->Add(std::make_shared<Sphere>(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

    std::shared_ptr<Metal> material3 = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    scene->Add(std::make_shared<Sphere>(Vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));

    PPMWriter* writer = new PPMWriter(std::cout);

	renderer.Render(*camera, *scene, *writer);

    delete writer;
    writer = nullptr;

	delete scene;
	scene = nullptr;

	delete camera;
	camera = nullptr;
}

int main()
{
	Renderer* renderer = new Renderer();

	RenderBasicScene(*renderer);

	delete renderer;
    renderer = nullptr;

	return 0;
}
