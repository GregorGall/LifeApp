#include "Controller/Controller.h"

Controller::Controller(LifeModel& modelRef, View& viewRef) : modelRef(modelRef), viewRef(viewRef)
{
  auto cellProbe = [&](const QPoint& cell){ return bool(modelRef.readData()(cell.y(), cell.x())); };

  viewConnect();
  viewRef.setReadFnc(cellProbe);
  viewRef.resize(QSize(modelRef.readData().rows(), modelRef.readData().cols()));
}

void Controller::viewConnect()
{
  QObject::connect(this,   SIGNAL(newFrame()), viewRef.playGround, SLOT(repaint()));
  QObject::connect(this,   SIGNAL(newFrame()), this,               SLOT(updateStatus()));

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

  auto& delay = changes[StatusProperty::Delay];
  auto& fieldSize = changes[StatusProperty::FieldSize];
  auto& engineType = changes[StatusProperty::EngineType];

  QMap<StatusProperty, std::function<void()>> cntrlFnc;
  cntrlFnc[StatusProperty::FieldSize]  = [&](){ this->resize(fieldSize.toSize()); };
  cntrlFnc[StatusProperty::EngineType] = [&](){ this->setEngine(static_cast<Life::EngineType>(engineType.toInt())); };
  cntrlFnc[StatusProperty::Delay]      = [&](){ this->setDelay(static_cast<std::chrono::milliseconds>(delay.toInt())); };

  for(auto it = changes.begin(); it != changes.end(); ++it) {
    cntrlFnc[it.key()]();
  }

}
