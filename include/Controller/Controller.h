#pragma once
#include <QApplication>
#include "View/View.h"
#include "LifeModel.h"

class Controller : public QObject
{

  Q_OBJECT

  using LifeModel = Life::LifeModel;

public:

  Controller(LifeModel& modelRef, View& viewRef);

  ~Controller();

  void init();

  bool readCell(const QPoint& cell);

public slots:

  void stop();

  void run();

  void toggleRun();

  void toggleCell(const QPoint& cell);

  void clearDesk();

  void createGlider();

private:

  View& viewRef;

  LifeModel& modelRef;

  std::thread modelThread;

  const QString runState = "Life is in process";
  const QString stopState = "Life is stopped";

};

