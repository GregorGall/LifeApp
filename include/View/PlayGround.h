#pragma once
#include <QtWidgets>
#include <functional>

class PlayGround: public QWidget
{

  Q_OBJECT

  using stateFnc = std::function<bool(const QPoint&)>;

public:

  PlayGround(QWidget* parent = nullptr);

  ~PlayGround();

  void clearFocus();

  const QPoint& getCurrentFocus();

  void resize(int cols, int rows);

  void setReadFnc(const stateFnc& stateCheck);

signals:

  void togglePoint(const QPoint& pos);

protected:

  void paintEvent(QPaintEvent* event);

  void mousePressEvent(QMouseEvent* pe);

private:

  void drawField(QPainter& painter);

  QPoint posToNums(const QPoint& pos);

  void toggleFocus(const QPoint& mousePos);

  void moveFocus(const QPoint& mousePos);

private:

  QSize quantity{0, 0};

  QSizeF patch{0, 0};

  QSizeF frame{0, 0};

  QPoint focus{0, 0};

  int pointRad = 1;

  int objRad = 5;

  stateFnc pointState = [](const QPoint&){ return false; };

  QPen dotPen = QPen(Qt::gray, 2*pointRad, Qt::SolidLine, Qt::RoundCap);
  QPen objPen = QPen(Qt::gray, 2*objRad, Qt::SolidLine, Qt::RoundCap);
  QPen focusPen = QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap);

};
