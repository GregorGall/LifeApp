#include "Controller/Controller.h"

Controller::Controller(LifeModel& modelRef, View& viewRef) : modelRef(modelRef),
                                                             viewRef(viewRef)
{
}

Controller::~Controller()
{
}

void Controller::init()
{
  auto& data = modelRef.readData();
  viewRef.resize(QSize(data.rows(), data.cols()));
}

bool Controller::readCell(const QPoint& cell)
{
  return modelRef.readData()(cell.x(), cell.y());
}

void Controller::stop()
{
  modelRef.stop();
  modelThread.join();
  viewRef.printStatus(stopState);
}

void Controller::run()
{
  auto viewCallBack = [&](){ viewRef.update(); };
  modelThread = std::thread(&LifeModel::run, std::ref(modelRef), viewCallBack);
  viewRef.printStatus(runState);
}

void Controller::toggleRun()
{
  modelThread.joinable() ? stop() : run();
}

void Controller::toggleCell(const QPoint& cell)
{
  modelRef.toggleCell(cell.x(), cell.y());
  viewRef.update();
}

void Controller::clearDesk()
{
//    modelRef.clear();
    for(int i = 0; i < modelRef.readData().rows(); ++i) {
      for(int j = 0; j < modelRef.readData().cols(); ++j) {
        if(bool(modelRef.readData()(i, j))){ modelRef.toggleCell(i,j); }
      }
    }

    viewRef.update();
}

void Controller::createGlider()
{
  const QPoint& cell = viewRef.playGround->getCurrentFocus();
  int row = cell.x();
  int col = cell.y();
  using cellGroup = std::list<std::pair<int, int>>;
  cellGroup glider{ {row, col},
                    {row + 1, col + 1},
                    {row + 1, col + 2},
                    {row + 2, col    },
                    {row + 2, col + 1} };

  modelRef.toggleGroup(glider);
  viewRef.update();
}
