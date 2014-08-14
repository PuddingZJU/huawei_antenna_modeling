#include "NansyMenu.h"
#include <QPoint>

NansyMenu::NansyMenu(const QString & title, QWidget * parent)
	: QMenu(title, parent)
{

}

NansyMenu::~NansyMenu()
{

}

void NansyMenu::enterEvent(QEvent * event)
{
	emit entered();
}

void NansyMenu::leaveEvent(QEvent * event)
{
	emit leaved();
}