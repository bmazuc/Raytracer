#include "Panel/SceneFilePanel.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QDir>

SceneFilePanel::SceneFilePanel(QWidget* parent)
    : QWidget(parent)
{
    SetupUI();
    SetupConnections();
}

void SceneFilePanel::SetupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* fileLayout = new QHBoxLayout();

    mainLayout->addWidget(new QLabel("Scene JSON file", this));

    const QString defaultPath =
        QDir(QCoreApplication::applicationDirPath()).filePath("basic_scene.json");
    fileEdit = new QLineEdit(defaultPath, this);
    fileEdit->setPlaceholderText("Select a scene JSON file");

    browseButton = new QPushButton("Browse...", this);
    browseButton->setFixedWidth(90);

    fileLayout->addWidget(fileEdit, 1);
    fileLayout->addWidget(browseButton);
    mainLayout->addLayout(fileLayout);
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
