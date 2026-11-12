#include "Panel/SceneFilePanel.h"

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

SceneFilePanel::SceneFilePanel(QWidget* parent)
    : QWidget(parent)
{
    SetupUI();
    SetupConnections();
}

void SceneFilePanel::SetupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(8);

    QGroupBox* groupBox = new QGroupBox("Scene", this);
    QVBoxLayout* groupLayout = new QVBoxLayout(groupBox);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);

    QHBoxLayout* fileLayout = new QHBoxLayout();

    const QString defaultPath =
        QDir(QCoreApplication::applicationDirPath()).filePath("Scenes/basic_scene.json");
    fileEdit = new QLineEdit(defaultPath, groupBox);
    fileEdit->setPlaceholderText("Select a scene JSON file");

    browseButton = new QPushButton("Browse...", groupBox);
    browseButton->setFixedHeight(fileEdit->sizeHint().height());
    browseButton->setObjectName("browseButton");
    browseButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    fileLayout->addWidget(fileEdit, 1);
    fileLayout->addWidget(browseButton);

    formLayout->addRow("Scene JSON file", fileLayout);

    groupLayout->addStretch();
    groupLayout->addLayout(formLayout);
    groupLayout->addStretch();

    mainLayout->addWidget(groupBox);
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
