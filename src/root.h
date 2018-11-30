#ifndef ROOT_H
#define ROOT_H
#include <QVector3D>

struct Sphere {
  QVector3D pos;
  QVector3D rgb;
  float radius;
};

typedef Sphere Root;

#endif  // ROOT_H