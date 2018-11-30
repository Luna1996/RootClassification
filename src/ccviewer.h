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

  CCData* raw;
  float* vetx;
  int* edge;
  int* face;
  char* result;
  Root** roots;

  SP* prog;
  QMatrix4x4 projection;
  GLuint buf[4];
  GLuint vao;

 public:
  CCViewer();
  void setRaw(CCData* raw);

 private:
  static SP* loadShaderProgram(QString urls[2]);

 private slots:
  void onWindowChanged(QQuickWindow* win);
  void init();
  void clean();
  void paint();
  void resizeGL();
};

struct ShaderInfo {
  QOpenGLShader::ShaderTypeBit type;
  QString url;
};

#endif  // CCVIEWER_H