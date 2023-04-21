#pragma once

#include <QMainWindow>
#include "View/Settings.h"
#include "ui_View.h"

class View : public QMainWindow, public Ui::View
{
  Q_OBJECT

  using stateFnc = std::function<bool(QPoint)>;

public:

  View(QWidget *parent = nullptr);

  ~View();

  void setReadFnc(const stateFnc& stateCheck);

  void updateStatus(const QString& message);

  void updateGeneration(int genNum);

  void resize(const QSize& fieldSize);

  const Settings* settings();

signals:

  void accepted();

private slots:

  void on_SettingsBtn_clicked();

private:

  const QString genTitle = "Generation №%1";

  Settings* settingsPtr{ new Settings(this) };

};
