#include "App/App.h"

App::App(int argc, char **argv): QApp(argc, argv)
{
  model.setDelay(initDelay);
  view.setStatus({ Settings::engineType[0], QString::number(initDelay.count()), "0", "" });
}

int App::exec() {
  return QApp.exec();
}
