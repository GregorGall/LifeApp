#pragma once

#include <QMainWindow>
#include "View/Settings.h"
#include "ui_View.h"

class View : public QMainWindow, public Ui::View
{
  Q_OBJECT

  using stateFnc = std::function<bool(QPoint)>;

  static constexpr double initWidthPart{ 0.5 };
  static constexpr double initHeightPart{ 0.65 };

public:

  static const QString runStatus;

  static const QString stopStatus;

public:

  View(double widthPart = initWidthPart, double heightPart = initHeightPart, QWidget *parent = nullptr);

  const Settings* settings();

  void updateStatus();

  void resize(const QSize& fieldSize);

  void setReadFnc(const stateFnc& stateCheck);

  void setStatus(StatusProperty index, const QString& value);

  void setStatus(QVector<QString> status);

signals:

  void accepted();

private slots:

  void aboutMessage();

  void setupGeometry(double widthPart, double heightPart);

private:

  // Memory cleared by Qt because of parent ptr
  Settings* settingsPtr{ new Settings(this) };

  QVector<QString> statusArgs = { "-", "-", "-", "-" };

  const QString statusTemplate = "Engine: %1, Delay: %2ms, Generation: %3 %4";

};
