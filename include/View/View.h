#pragma once

#include <QMainWindow>
#include "ui_View.h"
#include "LifeModel.h"

/*
  Файл ui_View.h создается uic компилятором при получении формы
  в файле содержится c++ код описывающий форму. Один из вариантов
  создания интерфейса наследование класса этой формы и вызов метода
  setupUi который в этом случае становится доступен в классе QWidget.
  Название класса формы от которого требуется наследование указывается в
  самой форме.
*/

class View : public QMainWindow, public Ui::View
{
  Q_OBJECT

  using LifeModel = Life::LifeModel;

public:

  View(LifeModel& modelRef, QWidget *parent = nullptr);

  ~View();

  bool readCell(QPoint cell);

public slots:

  void toggleCell(QPoint cell);

  void toggleRun();

private:

  void stop();

  void run();

private:

  LifeModel& modelRef;

  std::thread modelThread;

};
