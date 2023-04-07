#pragma once
#include <QtWidgets>
#include <functional>

class PlayGround: public QWidget
{

  Q_OBJECT

  using stateFnc = std::function<bool(QPoint)>;

public:

  PlayGround(QWidget* parent = nullptr);

  ~PlayGround();

  void clearFocus();

  QPoint getCurrentFocus();

  void resize(int cols, int rows);

  void setStateCheck(const stateFnc& stateCheck);

signals:

  void togglePoint(QPoint pos);

protected:

  void paintEvent(QPaintEvent* event);

  void mousePressEvent(QMouseEvent* pe);

private:

  void drawField(QPainter& painter);

  QPoint posToNums(const QPoint& pos);

  void toggleFocus(const QPoint& mousePos);

private:

  QSize quantity{30, 30};

  QSizeF patch;

  QSizeF frame;

  QPoint focus{0, 0};

  int pointRad = 1;

  int objRad = 5;

  stateFnc pointState = [](QPoint){ return false; };

  QPen dotPen = QPen(Qt::gray, 2*pointRad, Qt::SolidLine, Qt::RoundCap);
  QPen objPen = QPen(Qt::gray, 2*objRad, Qt::SolidLine, Qt::RoundCap);
  QPen focusPen = QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap);

};
