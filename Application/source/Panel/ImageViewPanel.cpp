#include "Panel/ImageViewPanel.h"
#include "ImageView.h"
#include "UI/LayoutHelper.h"

#include <QVBoxLayout>
#include <QGroupBox>

ImageViewPanel::ImageViewPanel(QWidget* parent)
	: QWidget(parent)
{
	SetupUI();
	SetupConnections();
}

void ImageViewPanel::SetupUI()
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	LayoutHelper::SetupPanelLayout(mainLayout);

	QGroupBox* groupBox = new QGroupBox("Image", this);
	QVBoxLayout* groupLayout = new QVBoxLayout(groupBox);

	imageView = new ImageView(groupBox);

	groupLayout->addWidget(imageView);

	mainLayout->addWidget(groupBox);
}

void ImageViewPanel::SetupConnections()
{
	connect(this, &ImageViewPanel::SetImage, imageView, &ImageView::SetImage);
}