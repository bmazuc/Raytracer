#include "Raytracer.h"

#include "Application/RaytracerWindow.h"
#include "Application/Controller/RenderController.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    RaytracerWindow window(nullptr, "Raytracer", 1280, 720);

    window.show();

    return app.exec();

	return 0;
}
