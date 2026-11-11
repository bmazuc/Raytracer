#ifndef RAYTRACER_APPLICATION_SCENE_FILE_PANEL_H
#define RAYTRACER_APPLICATION_SCENE_FILE_PANEL_H

#include <QWidget>
#include <QString>

class QLineEdit;
class QPushButton;

class SceneFilePanel : public QWidget
{
    Q_OBJECT

public:
    explicit SceneFilePanel(QWidget* parent = nullptr);
    QString GetScenePath() const;

private:
    void SetupUI();
    void SetupConnections();

    void BrowseFile();

    QLineEdit* fileEdit = nullptr;
    QPushButton* browseButton = nullptr;
};

#endif // RAYTRACER_APPLICATION_SCENE_FILE_PANEL_H