#include "Panel/ImageViewPanel.h"
#include "ImageView.h"
#include "UI/LayoutHelper.h"

#include <QVBoxLayout>
#include <QGroupBox>

QString ImageViewPanel::GetGroupTitle() const
{
	return "Image";
}

void ImageViewPanel::SetupUI()
{
	imageView = new ImageView(groupBox);

	groupLayout->addWidget(imageView);
}

void ImageViewPanel::SetupConnections()
{
	connect(this, &ImageViewPanel::SetImage, imageView, &ImageView::SetImage);
}