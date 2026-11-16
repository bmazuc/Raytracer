#ifndef RAYTRACER_APPLICATION_SCENE_FILE_PANEL_H
#define RAYTRACER_APPLICATION_SCENE_FILE_PANEL_H

#include "Panel/GroupBoxPanel.h"
#include <QString>

class QLineEdit;
class QPushButton;

/**
 * Provides controls for selecting the json scene file to load.
 */
class SceneFilePanel : public GroupBoxPanel
{
    Q_OBJECT

public:
    using GroupBoxPanel::GroupBoxPanel;

    /**
     * Returns the path of the currently selected scene file.
     *
     * @return Selected scene file path.
     */
    QString GetScenePath() const;

private:
    QString GetGroupTitle() const override;

    void SetupUI() override;
    void SetupConnections() override;

    /**
     * Opens a json file selection dialog 
     * and updates the corresponding input field.
     */
    void BrowseFile();

    // Input field containing the JSON scene file path
    QLineEdit* fileEdit = nullptr;
    // Opens the JSON scene file selection dialog
    QPushButton* browseButton = nullptr;
};

#endif // RAYTRACER_APPLICATION_SCENE_FILE_PANEL_H