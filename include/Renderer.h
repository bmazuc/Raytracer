#ifndef __RAYTRACER_H_INCLUDED__
#define __RAYTRACER_H_INCLUDED__

struct Color;
class Scene;
class Camera;

class Raytracer
{
public:
	void Render(Camera* camera, Scene* scene, bool useAntiAliasing = true);

private:
	void WriteColor(Color color);
};

#endif // __RAYTRACER_H_INCLUDED__