#ifndef RAYTRACER_APPLICATION_IMAGE_VIEW_PANEL_H
#define RAYTRACER_APPLICATION_IMAGE_VIEW_PANEL_H

#include <QWidget>

class QImage;
class ImageView;

class ImageViewPanel : public QWidget
{
	Q_OBJECT

public:
	explicit ImageViewPanel(QWidget* parent = nullptr);

signals:
	void SetImage(const QImage& image);

private:
	void SetupUI();
	void SetupConnections();

	ImageView* imageView;
};

#endif // RAYTRACER_APPLICATION_IMAGE_VIEW_PANEL_H