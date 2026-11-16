#ifndef RAYTRACER_APPLICATION_IMAGE_VIEW_H
#define RAYTRACER_APPLICATION_IMAGE_VIEW_H

#include <QWidget>
#include <QImage>
#include <QPointF>

class QMouseEvent;
class QWheelEvent;
class QPainter;

/**
 * Provides an interactive widget for displaying rendered images.
 *
 * Supports image scaling, zooming, panning and automatic fitting
 * of the image to the available widget area.
 *
 * Handles mouse and wheel events to provide interactive navigation.
 */
class ImageView : public QWidget
{
	Q_OBJECT

public:
	explicit ImageView(QWidget* parent = nullptr);

    /**
     * Replaces the current image and refreshes the widget display.
     *
     * @param image New image to display.
     */
	void SetImage(const QImage& image);
    /**
     * Resets the image content and refreshes the widget.
     */
	void Clear();

    /**
     * Scales and positions the image to fit the available widget area.
     */
	void FitImage();
    /**
     * Restores the initial zoom and image positioning.
     */
	void ResetZoom();

protected:
    /**
     * Handles image rendering, scaling and positioning.
     *
     * @param event Paint event.
     */
    void paintEvent(QPaintEvent* event) override;
    /**
     * Recalculates the image positioning when automatic fitting is enabled.
     *
     * @param event Resize event.
     */
    void resizeEvent(QResizeEvent* event) override;

    /**
     * Handles mouse presses used to initiate image dragging.
     *
     * @param event Mouse press event.
     */
    void mousePressEvent(QMouseEvent* event) override;
    /**
     * Updates image positioning while the user drags the image.
     *
     * @param event Mouse movement event.
     */
    void mouseMoveEvent(QMouseEvent* event) override;
    /**
     * Handles the release of a mouse button during image interaction.
     *
     * @param event Mouse release event.
     */
    void mouseReleaseEvent(QMouseEvent* event) override;
    /**
     * Handles double-click interactions with the displayed image.
     *
     * @param event Mouse double-click event.
     */
    void mouseDoubleClickEvent(QMouseEvent* event) override;

    /**
     * Handles mouse wheel events to control image zoom.
     *
     * @param event Mouse wheel event.
     */
    void wheelEvent(QWheelEvent* event) override;

private:
    /**
     * Takes the current zoom level and image offset into account
     * to determine the image's displayed geometry.
     *
     * @return Rectangle occupied by the displayed image.
     */
    QRectF GetImageRect() const;

    /**
     * Adjusts the zoom level while preserving the visual position
     * of the point around which the zoom is performed.
     *
     * @param position Position around which the zoom is applied.
     * @param factor Zoom multiplier.
     */
    void ZoomAt(const QPointF& position, double factor);

private:
    QImage image;

    // Current image zoom multiplier
    float zoom = 1.0f;
    float minZoom = 0.05f;
    float maxZoom = 20.0f;

    // Display-space translation applied to the image
    QPointF offset = QPointF(0.0f, 0.0f);

    // Previous mouse position used to calculate drag displacement
    QPointF lastMousePosition;

    bool isDragging = false;
    // Whether the image is automatically fitted after widget resizing
    bool fitToWindow = true;

};

#endif // RAYTRACER_APPLICATION_IMAGE_VIEW_H