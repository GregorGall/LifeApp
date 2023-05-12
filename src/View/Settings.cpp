#include "View/Settings.h"

const QVector<QString> Settings::engineType{"Common", "Thread", "OpenMP", "Cuda"};

Settings::Settings(QWidget *parent): QDialog{parent}
{
  setupUi(this);
  connect(this, SIGNAL(accepted()), this, SLOT(apply()));
  connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), SIGNAL(accepted()));

  EngineButton->setId(commonBtn, 0);
  EngineButton->setId(threadBtn, 1);
  EngineButton->setId(openMPBtn, 2);
  EngineButton->setId(cudaBtn,   3);
}

void Settings::apply()
{
  QMap<StatusProperty, QVariant> data;
  data[StatusProperty::Delay] = int{ delayLine->value() };
  data[StatusProperty::EngineType] = EngineButton->checkedId();
  data[StatusProperty::FieldSize] = QSize{ sizeX->value(), sizeY->value() };

  changes.clear();
  for(auto it = data.begin(); it != data.end(); ++it) {
    if( !currentState.contains(it.key()) || currentState[it.key()] != it.value() ) {
      currentState[it.key()] = it.value();
      changes[it.key()] = it.value();
    }
  }

}

const QMap<StatusProperty, QVariant> &Settings::getChanges() const
{
  return changes;
}

void Settings::setSize(const QSize &value)
{
  sizeX->setValue(value.width());
  sizeY->setValue(value.height());
  currentState[StatusProperty::FieldSize] = value;
}
