#include "App/App.h"

App::App(int argc, char **argv): QApp(argc, argv)
{
  model.setDelay(initDelay);

  view.setStatus(StatusProperty::RunStatus, "");
  view.setStatus(StatusProperty::EngineType, Settings::engineType[static_cast<int>(0)]);
  view.setStatus(StatusProperty::Delay, QString::number(initDelay.count()));
  view.setStatus(StatusProperty::Generation, QString::number(0));
}

int App::exec() {
  return QApp.exec();
}
