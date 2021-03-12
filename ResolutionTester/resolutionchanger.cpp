#include "resolutionchanger.h"

ResolutionChanger::ResolutionChanger(QWidget *parent, int horizontal, int vertical)
	:QDialog(parent)
{
	setupUi(this);

	QRegExpValidator *validator = new QRegExpValidator(QRegExp("[1-9][0-9]{0,10}"), this);

	horizontalLineEdit->setValidator(validator);
	verticalLineEdit->setValidator(validator);

	horizontalLineEdit->setText(QString().setNum(horizontal));
	verticalLineEdit->setText(QString().setNum(vertical));
}