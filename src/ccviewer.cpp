#include "ccviewer.h"
#include <QFile>
#include <QTextStream>

CCViewer::CCViewer()
    : raw(nullptr), result(nullptr), roots(nullptr), prog(nullptr) {
  connect(this, &QQuickItem::windowChanged, this, &CCViewer::onWindowChanged);
}

SP* CCViewer::loadShaderProgram(QString urls[2]) {
  SP* prog = new SP;
  ShaderInfo infos[2] = {{QOpenGLShader::Vertex, urls[0]},
                         {QOpenGLShader::Fragment, urls[1]}};
  for (ShaderInfo info : infos) {
    QFile f(info.url);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
      throw QString("can't read") + info.url;
    }
    QTextStream in(&f);
    prog->addCacheableShaderFromSourceCode(info.type, in.readAll());
  }

  return prog;
}

void CCViewer::onWindowChanged(QQuickWindow* win) {
  if (win) {
    win->setClearBeforeRendering(false);
    connect(win, &QQuickWindow::beforeSynchronizing, this, &CCViewer::init,
            Qt::DirectConnection);
    connect(win, &QQuickWindow::sceneGraphInvalidated, this, &CCViewer::clean,
            Qt::DirectConnection);
  }
}

void CCViewer::resizeGL() {
  float w = float(width()), h = float(height());
  glViewport(int(x()), int(y()), int(w), int(h));

  float aspect = w / h;
  const qreal zNear = -10, zFar = 10, fov = 120;
  projection.setToIdentity();
  projection.perspective(fov, aspect, zNear, zFar);
  projection.lookAt(QVector3D(5, 5, 5), QVector3D(.5, .5, .5),
                    QVector3D(0, 1, 0));
}

void CCViewer::init() {
  initializeOpenGLFunctions();
  glClearColor(1, 1, 1, 1);
  glLineWidth(1);
  resizeGL();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

#define TEST
#ifdef TEST
  QString urls[2] = {":/src/cc.vert", ":/src/cc.frag"};
  prog = loadShaderProgram(urls);
  prog->bindAttributeLocation("vertex", 0);
  prog->bindAttributeLocation("vcolor", 1);
  prog->bind();

  prog->setUniformValue(prog->uniformLocation("size"), float(width()),
                        float(height()));

  GLfloat vet[12] = {0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0};
  GLfloat col[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
  GLuint ind[4] = {0, 1, 2, 3};

  glGenBuffers(4, buf);

  glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, vet, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 4, ind,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, buf[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, col, GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf[3]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 4, ind,
               GL_DYNAMIC_DRAW);

//  prog->release();
#endif

  connect(window(), &QQuickWindow::beforeRendering, this, &CCViewer::paint,
          Qt::DirectConnection);
}

void CCViewer::clean() {}

void CCViewer::paint() {
  prog->setUniformValue(prog->uniformLocation("mvp"), projection);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf[1]);
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, nullptr);
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf[3]);
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, nullptr);
}