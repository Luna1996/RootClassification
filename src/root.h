#ifndef ROOT_H
#define ROOT_H
#include <QVector3D>

struct Sphere {
  QVector3D pos;
  QVector3D rgb;
  float radius;

  static bool inThisSphere(Sphere s, QVector3D p) {
    return s.pos.distanceToPoint(p) <= s.radius ? true : false;
  }
};

typedef Sphere Root;

#endif  // ROOT_H
