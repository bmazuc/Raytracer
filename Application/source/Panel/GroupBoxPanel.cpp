#include "Panel/GroupBoxPanel.h"

#include <QGroupBox>
#include <QVBoxLayout>

void GroupBoxPanel::SetupContainer()
{
	groupBox = new QGroupBox(GetGroupTitle(), this);
	groupLayout = CreateGroupLayout();

	mainLayout->addWidget(groupBox);
}

QBoxLayout* GroupBoxPanel::CreateGroupLayout()
{
	return new QVBoxLayout(groupBox);
}