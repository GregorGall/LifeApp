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

  View(QWidget *parent = nullptr);

  void setReadFnc(const stateFnc& stateCheck);

  void resize(const QSize& fieldSize);

  const Settings* settings();

  void setStatus(StatusProperty index, const QString& value);

  void updateStatus();

signals:

  void accepted();

private:

  Settings* settingsPtr{ new Settings(this) }; //WARNING need shared_ptr

  QVector<QString> statusArgs = { "-", "-", "-", "-" };

  const QString statusTemplate = "Engine: %1, Delay: %2ms, Generation: %3 %4";

};
