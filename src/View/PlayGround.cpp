#include "View/PlayGround.h"

PlayGround::PlayGround(QWidget* parent) : QWidget(parent)
{
}

PlayGround::~PlayGround()
{
}

QPoint PlayGround::posToNums(const QPoint &pos)
{
  auto rect = this->rect();
  QSizeF dims{ rect.width()/quantity.width(), rect.height()/quantity.height() };
  int x = round(pos.x() / dims.width());
  int y = round(pos.y() / dims.height());

  return {x, y};
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

QPoint PlayGround::getCurrentFocus()
{
  return focus;
}

void PlayGround::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setPen(QPen(Qt::gray, 2*pointRad, Qt::SolidLine, Qt::RoundCap));

  drawField(painter);
}

void PlayGround::drawField(QPainter& painter)
{
  auto rect = this->rect();
  QSizeF dims{ rect.width()/quantity.width(), rect.height()/quantity.height() };

  dims.setWidth( rect.width()/quantity.width() );
  dims.setHeight( rect.height()/quantity.height() );

  for(int i = 0; i < quantity.width() - 1; ++i){
    for(int j = 0; j < quantity.height() - 1; ++j){
      painter.drawPoint((i+1)*dims.width(),(j+1)*dims.height());
    }
  }

  if(!focus.isNull()) {
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap));
    painter.drawEllipse(focus.x()*dims.width() - objRad,
                        focus.y()*dims.height() - objRad, 2*objRad, 2*objRad);
  }

  for(auto& point: testDots){
    painter.setPen(QPen(Qt::gray, 2*objRad, Qt::SolidLine, Qt::RoundCap));
    painter.drawPoint(point.x()*dims.width(), point.y()*dims.height());
  }

}

void PlayGround::mousePressEvent(QMouseEvent *pe)
{
  auto mousePos = posToNums(pe->pos());

  if( pe->button() == Qt::LeftButton ) {
    testDots.push_back(mousePos);
    emit pointToggle(mousePos);
  }

  if( pe->button() == Qt::RightButton ) {
    toggleFocus(mousePos);
  }

  update();
}
