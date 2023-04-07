#include "View/PlayGround.h"

PlayGround::PlayGround(QWidget* parent) : QWidget(parent)
{
}

PlayGround::~PlayGround()
{
}

QPoint PlayGround::getCurrentFocus()
{
  return focus;
}

void PlayGround::clearFocus()
{
  focus = {0, 0};
}

void PlayGround::resize(int cols, int rows)
{
  quantity = {cols, rows};
  update();
}

void PlayGround::setStateCheck(const stateFnc &stateCheck)
{
  pointState = stateCheck;
}

void PlayGround::toggleFocus(const QPoint &mousePos)
{
  if(focus.isNull()) {
    focus = {mousePos.x(), mousePos.y()};
  }
  else {
    focus = {0, 0};
  }
}

QPoint PlayGround::posToNums(const QPoint &pos)
{
  int x = round( (pos.x() - frame.width()) / patch.width());
  int y = round( (pos.y() - frame.height()) / patch.height());

  return {x, y};
}

void PlayGround::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  auto rect = this->rect();
  patch.setWidth(qreal(rect.width()/quantity.width()));
  patch.setHeight(qreal(rect.height()/quantity.height()));
  frame.setWidth(0.5*patch.width());
  frame.setHeight(0.5*patch.height());

  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setPen(dotPen);
  drawField(painter);
}

void PlayGround::drawField(QPainter& painter)
{

  for(int i = 0; i < quantity.width(); ++i){
    for(int j = 0; j < quantity.height(); ++j){
      pointState(QPoint(i, j)) ? painter.setPen(objPen) : painter.setPen(dotPen);
      painter.drawPoint(i*patch.width() + frame.width(),j*patch.height() + frame.height());
    }
  }

  if(!focus.isNull()) {
    painter.setPen(focusPen);
    int x = focus.x()*patch.width() - objRad;
    int y = focus.y()*patch.height() - objRad;
    painter.drawEllipse(x, y, 2*objRad, 2*objRad);
  }
}

void PlayGround::mousePressEvent(QMouseEvent *pe)
{
  auto mousePos = posToNums(pe->pos());

  if( pe->button() == Qt::LeftButton ) {
    emit togglePoint(mousePos);
  }

  if( pe->button() == Qt::RightButton ) {
    toggleFocus(mousePos);
  }

  update();
}
