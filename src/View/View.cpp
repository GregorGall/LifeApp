#include "View/View.h"

const QString View::runStatus{"executes"};

const QString View::stopStatus{"stopped"};

View::View(double widthPart, double heightPart, QWidget *parent) : QMainWindow(parent)
{
  setupUi(this);
  connect(settingsPtr, SIGNAL(accepted()), this, SIGNAL(accepted()));
  connect(SettingsBtn, SIGNAL(clicked()), settingsPtr, SLOT(show()));

  auto userScreen = QApplication::desktop()->screenGeometry();

  userScreen.setWidth(userScreen.width() * widthPart);
  userScreen.setHeight(userScreen.height() * heightPart);
  userScreen.moveCenter(QApplication::desktop()->screenGeometry().center());

  setGeometry(userScreen);
  LaunchBtn->setFocus();
  show();
}

void View::setReadFnc(const stateFnc &stateCheck)
{
  playGround->setReadFnc(stateCheck);
}

void View::resize(const QSize &fieldSize)
{
  settingsPtr->setSize(fieldSize);
  playGround->resize(fieldSize.width(), fieldSize.height());
}

const Settings *View::settings()
{
  return settingsPtr;
}

void View::setStatus(StatusProperty index, const QString& value)
{
    statusArgs[static_cast<int>(index)] = value;
    updateStatus();
}

void View::setStatus(QVector<QString> status)
{
  int count = 0;
  for(auto& value: status){
    setStatus(static_cast<StatusProperty>(count++), value);
  }
}

void View::updateStatus()
{
  auto message = statusTemplate;
  statusbar->showMessage(message.arg(statusArgs[0], statusArgs[1], statusArgs[2], statusArgs[3]));
}

