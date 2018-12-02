#ifndef CCVIEWER_H
#define CCVIEWER_H
#include <QMatrix4x4>
#include <QOpenGLFunctions_3_0>
#include <QOpenGLShaderProgram>
#include <QQuickItem>
#include <QQuickWindow>
#include "ccdata.h"
#include "root.h"

typedef QOpenGLShaderProgram SP;

class CCViewer : public QQuickItem, protected QOpenGLFunctions_3_0 {
  Q_OBJECT
  Q_PROPERTY(qreal d READ d WRITE setD)
  Q_PROPERTY(qreal a1 READ a1 WRITE setA1)
  Q_PROPERTY(qreal a2 READ a2 WRITE setA2)

  Root** roots;
  CCData* raw;
  char* mark;

  SP* prog;
  QMatrix4x4 P, V;
  GLuint vao;
  struct {
    GLuint m, v, e, f;
  } vbo;
  float distance;
  QVector3D center;
  QVector2D eye;

 public:
  CCViewer();
  void setRaw(CCData* raw);
  void setMark(char* m);

  float d() const { return distance; }
  void setD(float d) {
    distance = d;
    bondView();
  }

  float a1() const { return eye[0]; }
  float a2() const { return eye[1]; }
  void setA1(float a1) {
    eye[0] = a1;
    bondView();
  }
  void setA2(float a2) {
    eye[1] = a2;
    bondView();
  }

 private:
  static SP* loadShaderProgram(QString urls[2]);
  void bondProjection();
  void bondView();

 private slots:
  void onWindowChanged(QQuickWindow* win);
  void init();
  void clean();
  void paint();
};

struct ShaderInfo {
  QOpenGLShader::ShaderTypeBit type;
  QString url;
};

#endif  // CCVIEWER_H