#include "App/App.h"

App::App(int argc, char **argv): QApp(argc, argv),
                                 model(initX, initY),
                                 controller(model, view)
{
  model.setDelay(std::chrono::milliseconds(150));
  view.setReadFnc([&](const QPoint& cell){ return controller.readCell(cell); });
  controller.init();

  QObject::connect(view.playGround, SIGNAL(togglePoint(QPoint)), &controller, SLOT(toggleCell(QPoint)));
  QObject::connect(view.LaunchBtn, SIGNAL(clicked(bool)), &controller, SLOT(toggleRun()));
  QObject::connect(view.ClearBtn, SIGNAL(clicked(bool)), &controller, SLOT(clearDesk()));
  QObject::connect(view.GliderAction, SIGNAL(triggered(bool)), &controller, SLOT(createGlider()));


  view.show();
}

int App::exec() {
  return QApp.exec();
}
