#include "Controller/Controller.h"

void Controller::run()
{
  auto viewCallBack = [&]() { emit newFrame(); };

  modelThread = std::thread(&LifeModel::run, std::ref(modelRef), viewCallBack);
  viewRef.setStatus(StatusProperty::RunStatus, View::runStatus);
}

void Controller::stop()
{
  modelRef.stop();
  modelThread.join();
  viewRef.setStatus(StatusProperty::RunStatus, View::stopStatus);
}

void Controller::resize(const QSize &fieldSize)
{
  if(modelThread.joinable()) { stop(); }

  //toggle(row, col) row -> y; col -> x
  modelRef.resize(fieldSize.height(), fieldSize.width());
  viewRef.resize(fieldSize);
  emit newFrame();
}

void Controller::setEngine(Life::EngineType type)
{
 modelRef.setEngine(type);
 viewRef.setStatus(StatusProperty::EngineType, Settings::engineType[static_cast<int>(type)]);
}

void Controller::setDelay(std::chrono::milliseconds delay)
{
 modelRef.setDelay(delay);
 viewRef.setStatus(StatusProperty::Delay, QString::number(delay.count()));
}

void Controller::toggleRun()
{
  modelThread.joinable() ? stop() : run();
}

void Controller::updateStatus()
{
  static int generation = 0;
  viewRef.setStatus(StatusProperty::Generation, QString::number(generation++));
}

void Controller::toggleCell(const QPoint& cell)
{
  //toggle(row, col) row -> y; col -> x
  modelRef.toggleCell(cell.y(), cell.x());
  emit newFrame();
}

void Controller::clearDesk()
{
  if(modelThread.joinable()) { stop(); }
  modelRef.clearDesk();
  emit newFrame();
}

void Controller::makeFigure(Life::makeFnc make)
{
  const QPoint& cell = viewRef.playGround->getCurrentFocus();

  //toggle(row, col) row -> y; col -> x
  modelRef.toggleGroup(make(cell.y(), cell.x()));
  emit newFrame();
}


