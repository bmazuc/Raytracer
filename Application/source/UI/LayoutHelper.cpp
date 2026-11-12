#include "UI/LayoutHelper.h"
#include "UI/UIConstants.h"

#include <QLayout>
#include <QFormLayout>

void LayoutHelper::SetupPanelLayout(QLayout* layout)
{
    layout->setContentsMargins(
        UIConstants::Layout::PanelMargin,
        UIConstants::Layout::PanelMargin,
        UIConstants::Layout::PanelMargin,
        UIConstants::Layout::PanelMargin
    );

    layout->setSpacing(UIConstants::Layout::PanelSpacing);

}

void LayoutHelper::SetupFormLayout(QFormLayout* layout)
{
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setHorizontalSpacing(UIConstants::Layout::FormHorizontalSpacing);
    layout->setVerticalSpacing(UIConstants::Layout::FormVerticalSpacing);
}