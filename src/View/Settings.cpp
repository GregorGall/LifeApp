#include "View/Settings.h"

Settings::Settings(QWidget *parent): QDialog{parent} {
  setupUi(this);
  connect(this,     SIGNAL(accepted()),    this, SLOT(apply()));
  connect(applyBtn, SIGNAL(clicked(bool)), SIGNAL(accepted()));

  EngineButton->setId(commonEngine, 1);
  EngineButton->setId(threadEngine, 2);
  EngineButton->setId(OMPEngine,    3);
  EngineButton->setId(cudaEngine,   4);
}

const QMap<QString, QVariant> &Settings::getChanges() const
{
  return changes;
}

void Settings::apply() {

  QMap<QString, QVariant> data;
  data[delayProperty] = int{ delayLine->value() };
  data[engineProperty] = EngineButton->checkedId();
  data[fieldProperty] = QSize{ sizeX->value(), sizeY->value() };

  changes.clear();
  for(auto it = data.begin(); it != data.end(); ++it) {
    if( !currentState.contains(it.key()) || currentState[it.key()] != it.value() ) {
      currentState[it.key()] = it.value();
      changes[it.key()] = it.value();
    }
  }

}
