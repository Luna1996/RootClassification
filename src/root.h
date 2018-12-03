#ifndef ROOT_H
#define ROOT_H
#include <QColor>
#include <QObject>
#include <QVector3D>

class Sphere : public QObject {
  Q_OBJECT

  Q_PROPERTY(QVector3D c MEMBER rgb)
  Q_PROPERTY(QVector3D xyz MEMBER pos)
  Q_PROPERTY(float r MEMBER radius)

 public:
  QVector3D rgb;
  QVector3D pos;
  float radius;

  Sphere(QObject* p = nullptr)
      : QObject(p), rgb(0, 0, 0), pos(0, 0, 0), radius(0) {}

  Sphere(const Sphere& s) {
    rgb = s.rgb;
    pos = s.pos;
    radius = s.radius;
  }
  static bool inThisSphere(Sphere s, QVector3D p) {
    return s.pos.distanceToPoint(p) <= s.radius ? true : false;
  }
};

typedef Sphere Root;

#endif  // ROOT_H
