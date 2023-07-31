#include "View/View.h"

const QString View::runStatus{"executes"};

const QString View::stopStatus{"stopped"};

View::View(double widthPart, double heightPart, QWidget *parent) : QMainWindow(parent)
{
  setupUi(this);
  connect(settingsPtr,    SIGNAL(accepted()),  this,         SIGNAL(accepted()));
  connect(SettingsBtn,    SIGNAL(clicked()),   settingsPtr,  SLOT(show()));
  connect(SettingsAction, SIGNAL(triggered()), settingsPtr,  SLOT(show()));
  connect(about,          SIGNAL(triggered()), this,         SLOT(aboutMessage()));
  connect(help,           SIGNAL(triggered()), this,         SLOT(helpMessage()));

  setupGeometry(widthPart, heightPart);
  LaunchBtn->setFocus();
  show();
}

void View::setupGeometry(double widthPart, double heightPart)
{
  auto userScreen = QApplication::primaryScreen()->geometry();

  userScreen.setWidth(userScreen.width() * widthPart);
  userScreen.setHeight(userScreen.height() * heightPart);
  userScreen.moveCenter(QApplication::primaryScreen()->geometry().center());

  setGeometry(userScreen);
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

void View::aboutMessage()
{

  QString msg = "The Game of Life, also known simply as Life is a cellular automation\ndevised by the British mathematician J.H. Conway.\n\n";
  msg += "Author: GregorGall\n";
  msg += "App version: " + QString(VERSION) + "\n";
  msg += "Commit: " + QString(COMMIT_HASH) + "\n";
  msg += "Build date: " + QString(TODAY) + "\n";
  msg += "Build time: " + QString(NOW) + "\n";

  QMessageBox::about(this, "About", msg);
}

void View::helpMessage()
{
  QString msg = "Main control:\n\n";
  msg += "LMB - toggle cell state\n";
  msg += "RMB - focus on cell\n";
  msg += "Double RMB - clear focus from cell\n\n";

  msg += "You can focus on cell and create some of default figures by click them on tool panel\n\n";
  msg += "Default figures shortcuts:\n";
  msg += "B - Boat\n";
  msg += "S - Stick\n";
  msg += "G - Glider\n";
  msg += "Q - Square\n";
  msg += "T - Toad\n";
  msg += "P - Pond\n";

  QMessageBox::information(this, "Help", msg);
}

void View::updateStatus()
{
  auto message = statusTemplate;
  statusbar->showMessage(message.arg(statusArgs[0], statusArgs[1], statusArgs[2], statusArgs[3]));
}

void View::toggleLaunchBtn()
{
  static int counter = 0;
  QVector<QString> name{"Launch","Stop"};
  QVector<QIcon> icon{QIcon(":/icons/media-playback-start.svg"), QIcon(":/icons/media-playback-pause.svg")};

  counter = (counter + 1) % 2;
  LaunchBtn->setText(name[counter]);
  LaunchBtn->setIcon(icon[counter]);
}

