#ifndef RAYTRACER_APPLICATION_IMAGE_VIEW_PANEL_H
#define RAYTRACER_APPLICATION_IMAGE_VIEW_PANEL_H

#include "Panel/GroupBoxPanel.h"

class QImage;
class ImageView;

/**
 * Provides the interface container for displaying rendered images.
 *
 * Embeds an ImageView widget and forwards image updates
 * to the image display component.
 */
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

	// Image display widget embedded in this panel
	ImageView* imageView;
};

#endif // RAYTRACER_APPLICATION_IMAGE_VIEW_PANEL_H