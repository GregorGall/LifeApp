#pragma once
#include <QApplication>
#include "View/View.h"
#include "LifeModel.h"
#include "Figures.h"

class Controller : public QObject
{
  Q_OBJECT

  using LifeModel = Life::LifeModel;

public:

  explicit Controller(LifeModel& modelRef, View& viewRef);

public slots:

  void exit();

  void setup();

  void clearDesk();

  void toggleRun();

  void updateStatus();

  void toggleCell(const QPoint& cell);

  void makeFigure(Life::makeFnc make);

private:

  void run();

  void stop();

  void resize(const QSize& fieldSize);

  void setEngine(Life::EngineType type);

  void setDelay(std::chrono::milliseconds delay);

  void viewConnect();

signals:

  void newFrame();

private:

  View& viewRef;

  LifeModel& modelRef;

  std::thread modelThread;

};

