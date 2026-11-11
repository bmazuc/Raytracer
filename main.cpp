#include "RaytracerWindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    int width = 1920;
    int height = 1080;

    if (argc >= 3)
    {
        width = std::stoi(argv[1]);
        height = std::stoi(argv[2]);
    }
    else if (argc >= 2)
    {
        width = std::stoi(argv[1]);
        height = static_cast<int>(height / (16.0f/9.0f));
        height = std::max(1, height);
    }

    RaytracerWindow window("Raytracer", 1920, 1080);

    window.show();
    window.showMaximized();

    return app.exec();
}
