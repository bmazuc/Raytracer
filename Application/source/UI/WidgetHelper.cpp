#include "UI/WidgetHelper.h"

#include <QPushButton>
#include <QLineEdit>

QPushButton* WidgetHelper::CreateBrowseButton(QLineEdit* associatedLineEdit, QWidget* parent)
{
    QPushButton* browseButton = new QPushButton("Browse...", parent);
    browseButton->setFixedHeight(associatedLineEdit->sizeHint().height());
    browseButton->setObjectName("browseButton");
    browseButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    return browseButton;
}