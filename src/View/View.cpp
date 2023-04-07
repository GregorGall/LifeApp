#include "View/View.h"

View::View(LifeModel& modelRef, QWidget *parent) : QMainWindow(parent),
                                                   modelRef(modelRef)
{
  setupUi(this);
  statusBar()->showMessage("Test message");
  playGround->setStateCheck([&](QPoint cell){ return readCell(cell); });

  connect(playGround, SIGNAL(togglePoint(QPoint)), this, SLOT(toggleCell(QPoint)));
  connect(LaunchBtn, SIGNAL(clicked(bool)), this, SLOT(toggleRun()));
}

View::~View(){

}

bool View::readCell(QPoint cell)
{
  return modelRef.readData()(cell.x(), cell.y());
}

void View::toggleCell(QPoint cell)
{
  modelRef.toggleCell(cell.x(), cell.y());
}

void View::toggleRun()
{
  modelThread.joinable() ? stop() : run();
}

void View::stop()
{
  modelRef.stop();
  modelThread.join();
}

void View::run()
{
  modelThread = std::thread(&LifeModel::run, std::ref(modelRef), [&](){ playGround->update(); });
}

