#pragma once

#include <QMainWindow>
#include "ui_View.h"

class View : public QMainWindow, public Ui::View
{
  Q_OBJECT

  using stateFnc = std::function<bool(QPoint)>;

public:

  View(QWidget *parent = nullptr);

  ~View();

  void setReadFnc(const stateFnc& stateCheck);

  void printStatus(const QString& message);

  void resize(const QSize& fieldSize);

};
