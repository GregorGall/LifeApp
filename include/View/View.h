#pragma once

#include <QWidget>
#include "ui_View.h"

/*
  Файл ui_View.h создается uic компилятором при получении формы
  в файле содержится c++ код описывающий форму. Один из вариантов
  создания интерфейса наследование класса этой формы и вызов метода
  setupUi который в этом случае становится доступен в классе QWidget.
  Название класса формы от которого требуется наследование указывается в
  самой форме.
*/

class View : public QWidget, public Ui::View
{
  Q_OBJECT

public:

  View(QWidget *parent = nullptr);
  ~View();

};
