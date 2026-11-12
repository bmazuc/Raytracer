#include "Panel/SceneFilePanel.h"
#include "UI/LayoutHelper.h"
#include "UI/WidgetHelper.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QDir>
#include <QStyle>
#include <QGroupBox>
#include <QFormLayout>

QString SceneFilePanel::GetGroupTitle() const
{
    return "Scene";
}

void SceneFilePanel::SetupUI()
{
    QFormLayout* formLayout = new QFormLayout();
    formLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    LayoutHelper::SetupFormLayout(formLayout);

    QHBoxLayout* fileLayout = new QHBoxLayout();

    const QString defaultPath =
        QDir(QCoreApplication::applicationDirPath()).filePath("Scenes/basic_scene.json");
    fileEdit = new QLineEdit(defaultPath, groupBox);
    fileEdit->setPlaceholderText("Select a scene JSON file");

    browseButton = WidgetHelper::CreateBrowseButton(fileEdit, groupBox);

    fileLayout->addWidget(fileEdit, 1);
    fileLayout->addWidget(browseButton);

    formLayout->addRow("Scene JSON file", fileLayout);

    groupLayout->addLayout(formLayout);
}

void SceneFilePanel::SetupConnections()
{
    connect(browseButton, &QPushButton::clicked,
        this, &SceneFilePanel::BrowseFile);
}

QString SceneFilePanel::GetScenePath() const
{
    return fileEdit->text().trimmed();
}

void SceneFilePanel::BrowseFile()
{
    const QString path = QFileDialog::getOpenFileName(
        this,
        "Select scene JSON file",
        fileEdit->text(),
        "JSON files (*.json);;All files (*)"
    );

    if (!path.isEmpty())
    {
        fileEdit->setText(path);
    }
}
