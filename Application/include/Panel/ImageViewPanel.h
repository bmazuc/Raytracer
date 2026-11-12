#ifndef RAYTRACER_APPLICATION_IMAGE_VIEW_PANEL_H
#define RAYTRACER_APPLICATION_IMAGE_VIEW_PANEL_H

#include "Panel/GroupBoxPanel.h"

class QImage;
class ImageView;

class ImageViewPanel : public GroupBoxPanel
{
	Q_OBJECT

public:
	using GroupBoxPanel::GroupBoxPanel;

signals:
	void SetImage(const QImage& image);

private:
	QString GetGroupTitle() const override;
	void SetupUI() override;
	void SetupConnections() override;

	ImageView* imageView;
};

#endif // RAYTRACER_APPLICATION_IMAGE_VIEW_PANEL_H