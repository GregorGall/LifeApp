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

  static const int initX = 30;

  static const int initY = 30;

  QApplication QApp;

  Life::LifeModel model;

  Controller controller;

  View view;

};
