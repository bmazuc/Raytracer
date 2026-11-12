#ifndef RAYTRACER_APPLICATION_SCENE_FILE_PANEL_H
#define RAYTRACER_APPLICATION_SCENE_FILE_PANEL_H

#include "Panel/GroupBoxPanel.h"
#include <QString>

class QLineEdit;
class QPushButton;

class SceneFilePanel : public GroupBoxPanel
{
    Q_OBJECT

public:
    using GroupBoxPanel::GroupBoxPanel;

    QString GetScenePath() const;

private:
    QString GetGroupTitle() const override;

    void SetupUI() override;
    void SetupConnections() override;

    void BrowseFile();

    QLineEdit* fileEdit = nullptr;
    QPushButton* browseButton = nullptr;
};

#endif // RAYTRACER_APPLICATION_SCENE_FILE_PANEL_H