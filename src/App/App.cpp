#include "App/App.h"

App::App(int argc, char **argv): QApp(argc, argv),
                                 model(30, 30),
                                 view(model)
{
  model.setDelay(std::chrono::milliseconds(150));
}

int App::exec() {
  view.show();
  return QApp.exec();
}
