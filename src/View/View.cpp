#include "View/View.h"

View::View(QWidget *parent) : QMainWindow(parent)
{
  setupUi(this);
  connect(settingsPtr, SIGNAL(accepted()), this, SIGNAL(accepted()));
}

View::~View()
{
}

void View::setReadFnc(const stateFnc &stateCheck)
{
  playGround->setReadFnc(stateCheck);
}

void View::updateStatus(const QString &message)
{
  statusBar()->showMessage(message);
}

void View::updateGeneration(int genNum)
{
  ControlBox->setTitle(genTitle.arg(genNum));
}

void View::resize(const QSize &fieldSize)
{
  playGround->resize(fieldSize.width(), fieldSize.height());
}

const Settings *View::settings() {
  return settingsPtr;
}

void View::on_SettingsBtn_clicked()
{
  settingsPtr->show();
}

