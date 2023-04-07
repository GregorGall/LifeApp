#include "View/View.h"

View::View(QWidget *parent) : QMainWindow(parent)
{
  setupUi(this);
}

View::~View()
{
}

void View::setReadFnc(const stateFnc &stateCheck)
{
  playGround->setReadFnc(stateCheck);
}

void View::printStatus(const QString &message)
{
  statusBar()->showMessage(message);
}

void View::resize(const QSize &fieldSize)
{
  playGround->resize(fieldSize.width(), fieldSize.height());
}
