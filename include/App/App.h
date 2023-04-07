#pragma once

#include <QApplication>
#include "View/View.h"
#include "LifeModel.h"

class App
{

public:

  App(int argc, char** argv);

  int exec();

private:

  QApplication QApp;

  Life::LifeModel model;

  View view;

};
