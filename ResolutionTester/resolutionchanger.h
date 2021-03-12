#pragma once
#include <QDialog>
#include "GeneratedFiles\ui_resolutionchanger.h"

class ResolutionChanger : public QDialog, public Ui::Dialog
{
	Q_OBJECT
public:
	ResolutionChanger(QWidget *parent = 0, int horizontal = 100, int vertical = 100);
};