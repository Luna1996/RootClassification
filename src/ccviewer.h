#ifndef CCVIEWER_H
#define CCVIEWER_H
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_0>
#include <QOpenGLShaderProgram>
#include <QQuickItem>
#include <QQuickWindow>
#include "ccdata.h"
#include "root.h"

typedef QOpenGLShaderProgram SP;

class CCViewer : public QQuickItem, protected QOpenGLFunctions_3_0 {
  Q_OBJECT

  Root** roots;
  CCData* raw;
  char* mark;

  SP* prog;
  float distance;
  QVector3D center, eye;
  QMatrix4x4 P;
  struct {
    QOpenGLBuffer *m, *v, *e, *f;
  } vbo;

 public:
  CCViewer();
  void setRaw(CCData* raw);
  void setMark(char* m);

 private:
  static SP* loadShaderProgram(QString urls[2]);
  void resizeGL();

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