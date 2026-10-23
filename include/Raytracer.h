#ifndef __RAYTRACER_H_INCLUDED__
#define __RAYTRACER_H_INCLUDED__

class Camera;
class Viewport;
struct Color;
struct Ray;

class Raytracer
{
public:
	~Raytracer();

	void Init(int inImageWidth, int inImageHeight);
	void Init(int inImageWidth, float aspectRatio);

	void Run();

private:
	Color GetRayColor(Ray ray);

private:
	int width = 256;
	int height = 256;

	Camera* camera;
	Viewport* viewport;
};

#endif // __RAYTRACER_H_INCLUDED__