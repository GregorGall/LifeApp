#pragma once

#include <QDialog>
#include <QSettings>
#include "ui_Settings.h"

class Settings : public QDialog, public Ui::Settings
{
  Q_OBJECT

public:

  Settings(QWidget* parent = nullptr);

  const QMap<QString, QVariant>& getChanges() const;

public slots:

  void apply();

private:

  QMap<QString, QVariant> changes;

  QMap<QString, QVariant> currentState;

  const QString fieldProperty{"FieldSize"};
  const QString delayProperty{"Delay"};
  const QString engineProperty{"EngineType"};

};
