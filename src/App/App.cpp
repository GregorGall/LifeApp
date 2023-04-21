#include "App/App.h"

App::App(int argc, char **argv): QApp(argc, argv)
{
  model.setDelay(initDelay);
  view.show();
}

int App::exec() {
  return QApp.exec();
}
