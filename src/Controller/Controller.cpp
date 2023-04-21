#include "Controller/Controller.h"

Controller::Controller(LifeModel& modelRef, View& viewRef) : modelRef(modelRef), viewRef(viewRef)
{
  auto cellProbe = [&](const QPoint& cell){ return bool(modelRef.readData()(cell.y(), cell.x())); };

  viewConnect();
  viewRef.setReadFnc(cellProbe);
  viewRef.resize(QSize(modelRef.readData().rows(), modelRef.readData().cols()));
}

Controller::~Controller()
{
}

void Controller::viewConnect()
{
  QObject::connect(this,   SIGNAL(newFrame()), viewRef.playGround, SLOT(repaint()));

  QObject::connect(viewRef.playGround,   SIGNAL(togglePoint(QPoint)), this, SLOT(toggleCell(QPoint)));
  QObject::connect(viewRef.LaunchBtn,    SIGNAL(clicked(bool)),       this, SLOT(toggleRun()));
  QObject::connect(viewRef.ClearBtn,     SIGNAL(clicked(bool)),       this, SLOT(clearDesk()));
  QObject::connect(viewRef.settings(),   SIGNAL(accepted()),          this, SLOT(setup()));
  QObject::connect(viewRef.GliderAction, &QAction::triggered, [&](){ makeFigure(Life::makeGlider); });
  QObject::connect(viewRef.StickAction,  &QAction::triggered, [&](){ makeFigure(Life::makeStick); });
  QObject::connect(viewRef.PondAction,   &QAction::triggered, [&](){ makeFigure(Life::makePond); });
  QObject::connect(viewRef.SquareAction, &QAction::triggered, [&](){ makeFigure(Life::makeSquare); });
}

void Controller::setup()
{
  auto& changes = viewRef.settings()->getChanges();

  QMap<QString, std::function<void()>> cntrlFnc;
  cntrlFnc["FieldSize"] = [&](){ this->resize(changes["FieldSize"].toSize()); };
  cntrlFnc["Delay"] = [&](){ this->setDelay(std::chrono::milliseconds(changes["Delay"].toInt())); };
  cntrlFnc["EngineType"] = [&](){ this->setEngine(Life::EngineType(changes["EngineType"].toInt())); };

  for(auto it = changes.begin(); it != changes.end(); ++it) {
    cntrlFnc[it.key()]();
  }

}
