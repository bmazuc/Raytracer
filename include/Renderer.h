#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

struct Color;
class Scene;
class Camera;
class PPMWriter;

class Renderer
{
public:
	void Render(const Camera& camera, const Scene& scene, const PPMWriter& ppmWriter) const;

	void UseAntialising(bool newState) { useAntiAliasing = newState; }

private:
	bool useAntiAliasing = true;
};

#endif // __RENDERER_H_INCLUDED__