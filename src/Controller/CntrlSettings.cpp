#include "Controller/Controller.h"

void Controller::run()
{
  auto viewCallBack = [&]() { emit newFrame(); };

  modelThread = std::thread(&LifeModel::run, std::ref(modelRef), viewCallBack);
  viewRef.updateStatus(runStatus);
}

void Controller::stop()
{
  modelRef.stop();
  modelThread.join();
  viewRef.updateStatus(stopStatus);
}

void Controller::resize(const QSize &fieldSize)
{
  if(modelThread.joinable()) { stop(); }
  modelRef.resize(fieldSize.width(), fieldSize.height());
  viewRef.resize(fieldSize);
  viewRef.update();
}

void Controller::setEngine(Life::EngineType type)
{
 modelRef.setEngine(type);
}

void Controller::setDelay(std::chrono::milliseconds delay)
{
 modelRef.setDelay(delay);
}

void Controller::toggleRun()
{
  modelThread.joinable() ? stop() : run();
}

void Controller::toggleCell(const QPoint& cell)
{
  //toggle(row, col) row -> y; col -> x
  modelRef.toggleCell(cell.y(), cell.x());
  viewRef.update();
}

void Controller::clearDesk()
{
  if(modelThread.joinable()) { stop(); }
  modelRef.clear();

  viewRef.updateGeneration(genNum = 0);
  viewRef.update();
}

void Controller::makeFigure(Life::makeFnc make)
{
  const QPoint& cell = viewRef.playGround->getCurrentFocus();

  //toggle(row, col) row -> y; col -> x
  modelRef.toggleGroup(make(cell.y(), cell.x()));
  viewRef.update();
}


