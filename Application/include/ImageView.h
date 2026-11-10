#ifndef RAYTRACER_APPLICATION_IMAGE_VIEW_H
#define RAYTRACER_APPLICATION_IMAGE_VIEW_H

#include <QWidget>
#include <QImage>
#include <QPointF>

class QMouseEvent;
class QWheelEvent;
class QPainter;


class ImageView : public QWidget
{
	Q_OBJECT

public:
	explicit ImageView(QWidget* parent = nullptr);

	void SetImage(const QImage& image);
	void Clear();

	void FitImage();
	void ResetZoom();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;

private:
    QRectF GetImageRect() const;

    void ZoomAt(const QPointF& position, double factor);

private:
    QImage image;

    float zoom = 1.0f;
    float minZoom = 0.05f;
    float maxZoom = 20.0f;

    QPointF offset = QPointF(0.0f, 0.0f);

    QPointF lastMousePosition;

    bool isDragging = false;
    bool fitToWindow = true;

};

#endif // RAYTRACER_APPLICATION_IMAGE_VIEW_H