#include "Raytracer.h"

#include "Application/RaytracerWindow.h"
#include "Application/Controller/RaytracerController.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char* argv[])
{
    const char* outputFile = (argc > 1) ? argv[1] : "image.png";

    QApplication app(argc, argv);

    RaytracerWindow window(nullptr, "Raytracer", 1280, 720);
 
    RaytracerController* controller = window.GetRaytracerController();
    if (controller)
    {
        controller->SetOutputFile(outputFile);
    }

    window.show();

    return app.exec();

	return 0;
}
