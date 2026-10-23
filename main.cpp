#include "Image.h"

using namespace std;

int main()
{
	Image* image = new Image(256, 256);

	image->Render();

	delete image;
	image = nullptr;

	return 0;
}
