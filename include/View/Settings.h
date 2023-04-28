#pragma once

#include <QDialog>
#include <QSettings>
#include "ui_Settings.h"

enum class StatusProperty {
  EngineType,
  Delay,
  Generation,
  RunStatus,
  FieldSize
};

class Settings : public QDialog, public Ui::Settings
{
  Q_OBJECT

public:

  static const QVector<QString> engineType;

public:

  Settings(QWidget* parent = nullptr);

  const QMap<StatusProperty, QVariant>& getChanges() const;

public slots:

  void apply();

private:

  QMap<StatusProperty, QVariant> changes;

  QMap<StatusProperty, QVariant> currentState;

};
