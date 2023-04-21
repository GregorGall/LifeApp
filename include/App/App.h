#pragma once

#include <QApplication>
#include "LifeModel.h"
#include "View/View.h"
#include "Controller/Controller.h"

class App
{

public:

  App(int argc, char** argv);

  int exec();

private:

  static const int initX{ 30 };

  static const int initY{ 30 };

  static constexpr std::chrono::milliseconds initDelay{ 25 };

  QApplication QApp;

  View view;

  Life::LifeModel model{initX, initY};

  Controller controller{model, view};

};
