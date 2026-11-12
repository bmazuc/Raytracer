#include "Panel/Panel.h"
#include "UI/LayoutHelper.h"

#include <QVBoxLayout>
#include <QGroupBox>

Panel::Panel(QWidget* parent)
	: QWidget(parent)
{
}

void Panel::InitPanel()
{
	mainLayout = CreateMainLayout();
	LayoutHelper::SetupPanelLayout(mainLayout);

	SetupContainer();
	SetupUI();
	SetupConnections();
}

QBoxLayout* Panel::CreateMainLayout()
{
	return new QVBoxLayout(this);
}