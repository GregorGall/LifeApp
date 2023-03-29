#include "View/View.h"

View::View(QWidget *parent) : QMainWindow(parent)
{
  setupUi(this);
  statusBar()->showMessage("Test message");
}

View::~View(){

}

