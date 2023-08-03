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

  static constexpr std::chrono::milliseconds initDelay{ 200 };

  QApplication QApp;

  View view;

  Life::LifeModel model;

  Controller controller{model, view};

};
