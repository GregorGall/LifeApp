#include "Controller/Controller.h"

Controller::Controller(LifeModel& modelRef, View& viewRef) : modelRef(modelRef), viewRef(viewRef)
{
  auto cellProbe = [&](const QPoint& cell){ return bool(modelRef.readData()(cell.y(), cell.x())); };

  viewConnect();
  viewRef.setReadFnc(cellProbe);
  resize(viewRef.playGround->fitSize());
}

void Controller::exit()
{
  if(modelThread.joinable()) {
    stop();
  }

  QApplication::exit();
}

void Controller::setup()
{
  auto& changes = viewRef.settings()->getChanges();

  const auto& delay = changes[StatusProperty::Delay];
  const auto& fieldSize = changes[StatusProperty::FieldSize];
  const auto& engineType = changes[StatusProperty::EngineType];

  QMap<StatusProperty, std::function<void()>> cntrlFnc;
  cntrlFnc[StatusProperty::FieldSize]  = [&](){ this->resize(fieldSize.toSize()); };
  cntrlFnc[StatusProperty::EngineType] = [&](){ this->setEngine(static_cast<Life::EngineType>(engineType.toInt())); };
  cntrlFnc[StatusProperty::Delay]      = [&](){ this->setDelay(static_cast<std::chrono::milliseconds>(delay.toInt())); };

  for(auto it = changes.begin(); it != changes.end(); ++it) {
    cntrlFnc[it.key()]();
  }

}

void Controller::viewConnect()
{
  QObject::connect(this, SIGNAL(redraw()),   viewRef.playGround, SLOT(update()));
  QObject::connect(this, SIGNAL(newFrame()), this,               SLOT(updateStatus()));
  QObject::connect(this, SIGNAL(newFrame()), this,               SIGNAL(redraw()));

  QObject::connect(viewRef.playGround, SIGNAL(togglePoint(QPoint)), this, SLOT(toggleCell(QPoint)));
  QObject::connect(viewRef.LaunchBtn,  SIGNAL(clicked(bool)),       this, SLOT(toggleRun()));
  QObject::connect(viewRef.ClearBtn,   SIGNAL(clicked(bool)),       this, SLOT(clearDesk()));
  QObject::connect(viewRef.ExitAction, SIGNAL(triggered()),         this, SLOT(exit()));
  QObject::connect(viewRef.settings(), SIGNAL(accepted()),          this, SLOT(setup()));

  QObject::connect(viewRef.GliderAction, &QAction::triggered, [&](){ makeFigure(Life::makeGlider); });
  QObject::connect(viewRef.StickAction,  &QAction::triggered, [&](){ makeFigure(Life::makeStick); });
  QObject::connect(viewRef.PondAction,   &QAction::triggered, [&](){ makeFigure(Life::makePond); });
  QObject::connect(viewRef.SquareAction, &QAction::triggered, [&](){ makeFigure(Life::makeSquare); });
  QObject::connect(viewRef.BoatAction,   &QAction::triggered, [&](){ makeFigure(Life::makeBoat); });
  QObject::connect(viewRef.ToadAction,   &QAction::triggered, [&](){ makeFigure(Life::makeToad); });
}


