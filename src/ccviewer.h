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
  Q_PROPERTY(bool show_center READ isShowCenter WRITE setShowCenter)

  QVector3D c1, c2;
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

  bool show_center;

 private:
  void _setRaw();
  void _setMark();

 public:
  Sphere* sphere;

  CCViewer();
  void setRaw(CCData* raw);
  void setMark(char* m, QVector3D c1, QVector3D c2);

  float d() const { return distance; }
  void setD(float d) {
    distance = d;
    bondView();
    window()->update();
  }

  float a1() const { return eye[0]; }
  float a2() const { return eye[1]; }
  void setA1(float a1) {
    eye[0] = a1;
    bondView();
    window()->update();
  }
  void setA2(float a2) {
    eye[1] = a2;
    bondView();
    window()->update();
  }

  bool isShowCenter() const { return show_center; }
  void setShowCenter(bool sc) {
    show_center = sc;
    window()->update();
  }

 private:
  static SP* loadShaderProgram(QString urls[2]);
  void drawSphere(QVector3D& pos, float r, int lats = 20, int longs = 20);
  void bondProjection();
  void bondView();
  void reconnectPaint() {
    disconnect(window(), &QQuickWindow::beforeRendering, this,
               &CCViewer::paint);
    connect(window(), &QQuickWindow::beforeRendering, this, &CCViewer::paint,
            Qt::DirectConnection);
  }

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