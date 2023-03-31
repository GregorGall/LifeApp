#pragma once
#include <QtWidgets>

class PlayGround: public QWidget
{

  Q_OBJECT

public:

  PlayGround(QWidget* parent = nullptr);

  ~PlayGround();

  void toggleFocus(const QPoint& mousePos);

  QPoint getCurrentFocus();

protected:

  void paintEvent(QPaintEvent* event);

  void mousePressEvent(QMouseEvent* pe);

private:

  void drawField(QPainter& painter);

  QPoint posToNums(const QPoint& pos);

signals:

  void pointToggle(QPoint pos);

private:

  QSizeF quantity{50, 50};

  QPoint focus{0, 0};

  int pointRad = 1;

  int objRad = 5;

  QVector<QPoint> testDots;

};
