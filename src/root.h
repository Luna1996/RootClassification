#ifndef ROOT_H
#define ROOT_H
#include <QColor>
#include <QObject>
#include <QVector3D>

class Sphere : public QObject {
  Q_OBJECT

  Q_PROPERTY(float r READ r WRITE setR)
  Q_PROPERTY(float g READ g WRITE setG)
  Q_PROPERTY(float b READ b WRITE setB)
  Q_PROPERTY(float mx READ x WRITE setX)
  Q_PROPERTY(float my READ y WRITE setY)
  Q_PROPERTY(float mz READ z WRITE setZ)
  Q_PROPERTY(float d MEMBER radius)

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

  float r() const { return rgb.x(); }
  float g() const { return rgb.y(); }
  float b() const { return rgb.z(); }
  float x() const { return pos.x(); }
  float y() const { return pos.y(); }
  float z() const { return pos.z(); }
  void setR(float r) { rgb.setX(r); }
  void setG(float g) { rgb.setY(g); }
  void setB(float b) { rgb.setZ(b); }
  void setX(float x) { pos.setX(x); }
  void setY(float y) { pos.setY(y); }
  void setZ(float z) { pos.setZ(z); }

  static bool inThisSphere(Sphere *s, QVector3D p) {
    return s->pos.distanceToPoint(p) <= s->radius ? true : false;
  }
};

typedef Sphere Root;

#endif  // ROOT_H
