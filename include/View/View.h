#pragma once

#include <QMainWindow>
#include "View/Settings.h"
#include "ui_View.h"

class View : public QMainWindow, public Ui::View
{
  Q_OBJECT

  using stateFnc = std::function<bool(QPoint)>;

public:

  static const QString runStatus;

  static const QString stopStatus;

public:

  View(double widthPart = 0.5, double heightPart = 0.65, QWidget *parent = nullptr);

  const Settings* settings();

  void updateStatus();

  void resize(const QSize& fieldSize);

  void setReadFnc(const stateFnc& stateCheck);

  void setStatus(StatusProperty index, const QString& value);

signals:

  void accepted();

private:

  // Memory cleared by Qt because of parent ptr
  Settings* settingsPtr{ new Settings(this) };

  QVector<QString> statusArgs = { "-", "-", "-", "-" };

  const QString statusTemplate = "Engine: %1, Delay: %2ms, Generation: %3 %4";

};
