#ifndef __RAYTRACER_H_INCLUDED__
#define __RAYTRACER_H_INCLUDED__

class Camera;
class Viewport;
struct Color;
struct Ray;
class Scene;

class Raytracer
{
public:
	Raytracer(int inImageWidth, int inImageHeight);
	Raytracer(int inImageWidth, float aspectRatio);

	~Raytracer();

	Scene* GetScene() { return scene; }
	const Scene* GetScene() const { return scene; }

	void SetScene(Scene* inScene);

	void Run();

private:
	void Render();

	Color GetRayColor(Ray ray);

private:
	int width = 256;
	int height = 256;

	Viewport* viewport = nullptr;
	Scene* scene = nullptr;
};

#endif // __RAYTRACER_H_INCLUDED__