#pragma once

#include <iostream>

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QDesktopWidget>

class myWidget: public QWidget
{

public:

  myWidget(QWidget* parent = nullptr) : QWidget(parent)
  {
    auto screen = QApplication::desktop()->screenGeometry();

    int height = screen.height()*0.3;
    int width = screen.width()*0.15;
    int initX = (screen.width() - width)*0.5;
    int initY = (screen.height() - height)*0.5;

    QWidget::setGeometry(initX, initY, width, height);
    QWidget::setMouseTracking(true);
  }

  virtual ~myWidget(){}

protected:

  void paintEvent(QPaintEvent *event)
  {
    QWidget::paintEvent(event);

    QPainter painter{this};

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(Qt::gray));
    painter.setPen(QPen(Qt::black));

    fieldDrawer(painter, *event);
    mouseTracker(painter, *event);

  }

  void fieldDrawer(QPainter& painter, QPaintEvent& event)
  {
    auto rect = event.rect();

    dims.setWidth( rect.width()/quantity.width() );
    dims.setHeight( rect.height()/quantity.height() );

    for(int i = 0; i < quantity.width(); ++i){
      for(int j = 0; j < quantity.height(); ++j){
        painter.drawRoundRect(QRectF(i*dims.width(),j*dims.height(),dims.width(),dims.height()),radius,radius);
      }
    }
  }

  void mouseTracker(QPainter& painter, QPaintEvent& event)
  {
    auto mouse = QWidget::mapFromGlobal(QCursor::pos());
    int initX = int(mouse.x() / dims.width()) * dims.width();
    int initY = int(mouse.y() / dims.height()) * dims.height();

    if(pressed){painter.setBrush(QBrush(Qt::green));}

    if(event.region().contains(mouse)) {
      painter.setPen(QPen(Qt::red, 3));
      painter.drawRoundRect(QRectF(initX,initY,dims.width(),dims.height()),radius,radius);
    }
  }

  void mousePressEvent(QMouseEvent* pe)
  {
    pressed = true;
    update();
  }

  void mouseReleaseEvent(QMouseEvent* pe)
  {

    pressed = false;
    update();
  }

  void mouseMoveEvent(QMouseEvent* pe)
  {
    update();
  }



private:

  bool pressed = false;
  QSizeF quantity{30, 30};
  QSizeF dims;
  int radius = 30;
};
