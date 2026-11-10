#include "ImageView.h"

#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPaintEvent>
#include <QResizeEvent>

#include <algorithm>
#include <cmath>

ImageView::ImageView(QWidget* parent)
	: QWidget(parent)
{
	setMinimumSize(200, 200);

	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
}

void ImageView::SetImage(const QImage& newImage)
{
	image = newImage;

	FitImage();

	update();
}

void ImageView::Clear()
{
	image = QImage();

	zoom = 1.0;
	offset = QPointF(0.0, 0.0);

	update();
}

QRectF ImageView::GetImageRect() const
{
    if (image.isNull())
    {
        return {};
    }

    const QSizeF scaledSize(image.width() * zoom, image.height() * zoom);

    const QPointF center = rect().center() + offset;

    return QRectF(
        center.x() - scaledSize.width() / 2.0,
        center.y() - scaledSize.height() / 2.0,
        scaledSize.width(),
        scaledSize.height()
    );
}

void ImageView::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.fillRect(rect(), QColor(35, 35, 35));

    if (image.isNull())
    {
        painter.setPen(Qt::lightGray);
        painter.drawText(rect(), Qt::AlignCenter, "No image");
        return;
    }

    painter.drawImage(GetImageRect(), image);
}


void ImageView::FitImage()
{
    if (image.isNull() || width() <= 0 || height() <= 0)
    {
        return;
    }

    const float scaleX = static_cast<float>(width()) / image.width();

    const float scaleY = static_cast<float>(height()) / image.height();

    zoom = std::clamp(std::min(scaleX, scaleY), minZoom, maxZoom);

    offset = QPointF(0.0f, 0.0f);

    fitToWindow = true;

    update();
}

void ImageView::ResetZoom()
{
    FitImage();
}

void ImageView::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    if (fitToWindow)
    {
        FitImage();
    }
}

void ImageView::ZoomAt(const QPointF& position, double factor)
{
    if (image.isNull())
        return;

    const float newZoom = std::clamp(zoom * static_cast<float>(factor), minZoom,maxZoom);

    if (newZoom == zoom)
        return;

    const QPointF widgetCenter = rect().center();

    // Offset between image center and cursor
    const QPointF cursorOffset = position - widgetCenter;

    // Position of the point in the image currently under the cursor, expressed relative to the centre of the image
    const QPointF imagePoint = (cursorOffset - offset) / zoom;

    // Keep the same point under the cursor after zooming.
    offset = cursorOffset - imagePoint * newZoom;

    zoom = newZoom;

    fitToWindow = false;

    update();
}

void ImageView::wheelEvent(QWheelEvent* event)
{
    const float factor = std::pow(1.15f, event->angleDelta().y() / 120.0f);

    ZoomAt(event->position(), factor);

    event->accept();
}

void ImageView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && !image.isNull())
    {
        isDragging = true;

        lastMousePosition = event->position();

        event->accept();
        return;
    }

    QWidget::mousePressEvent(event);
}

void ImageView::mouseMoveEvent(QMouseEvent* event)
{
    if (isDragging)
    {
        const QPointF delta = event->position() - lastMousePosition;

        offset += delta;

        lastMousePosition = event->position();

        fitToWindow = false;

        update();

        event->accept();
        return;
    }

    QWidget::mouseMoveEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && isDragging)
    {
        isDragging = false;

        event->accept();
        return;
    }

    QWidget::mouseReleaseEvent(event);
}

void ImageView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        FitImage();
        event->accept();
        return;
    }

    QWidget::mouseDoubleClickEvent(event);
}
