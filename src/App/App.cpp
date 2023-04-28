#include "App/App.h"

App::App(int argc, char **argv): QApp(argc, argv)
{
  model.setDelay(initDelay);

  view.setStatus(StatusProperty::RunStatus, "Opened");
  view.setStatus(StatusProperty::EngineType, Settings::engineType[static_cast<int>(0)]);
  view.setStatus(StatusProperty::Delay, QString::number(initDelay.count()));
  view.setStatus(StatusProperty::Generation, QString::number(0));

  view.show();
}

int App::exec() {
  return QApp.exec();
}
