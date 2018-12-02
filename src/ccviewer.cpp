#include "ccviewer.h"
#include <QFile>
#include <QTextStream>

CCViewer::CCViewer()
    : raw(nullptr),
      mark(nullptr),
      prog(nullptr),
      eye(1, 1, 1),
      vbo{new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer),
          new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer),
          new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer),
          new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)} {
  connect(this, &QQuickItem::windowChanged, this, &CCViewer::onWindowChanged);
  setFlag(QQuickItem::ItemHasContents);
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
    connect(win, &QQuickWindow::sceneGraphInitialized, this, &CCViewer::init,
            Qt::DirectConnection);
    connect(win, &QQuickWindow::beforeRendering, this, &CCViewer::paint,
            Qt::DirectConnection);
  }
}

void CCViewer::resizeGL() {
  float w = float(width()), h = float(height());
  glViewport(int(x()), int(y()), int(w), int(h));

  float aspect = w / h;
  float zNear = 0, zFar = distance, fov = 120.0;
  P.setToIdentity();
  P.perspective(fov, aspect, zNear, zFar);
  P.lookAt(eye * distance, center, QVector3D(0, 1, 0));
}

void CCViewer::init() {
  initializeOpenGLFunctions();

  vbo.m->create();
  vbo.v->create();
  vbo.e->create();
  vbo.f->create();

  QString urls[2] = {":/src/cc.vert", ":/src/cc.frag"};
  prog = loadShaderProgram(urls);
}

void CCViewer::setRaw(CCData* data) {
  raw = data;
  auto cc = raw->flat;

  center = raw->sphere->pos;
  distance = raw->sphere->radius;

  prog->bind();

  if (data) {
    vbo.v->allocate(static_cast<float*>(cc[0]),
                    int(raw->n1 * 3 * sizeof(float)));
    vbo.e->allocate(static_cast<int*>(cc[1]), int(raw->n2 * 2 * sizeof(int)));
    vbo.f->allocate(static_cast<int*>(cc[2]), int(raw->n3 * 3 * sizeof(int)));
  }
}

void CCViewer::setMark(char* m) {
  if (!raw) return;
  mark = m;

  prog->bind();

  if (m) {
    vbo.m->allocate(mark, int(raw->n1));
  }
}

void CCViewer::clean() {}

void CCViewer::paint() {
  glClearColor(1, 1, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  if (!raw) return;
  resizeGL();

  prog->bind();

  prog->setUniformValue(prog->uniformLocation("mvp"), P);

  int l1 = prog->attributeLocation("vertex");
  vbo.v->bind();
  prog->enableAttributeArray(l1);
  glVertexAttribPointer(GLuint(l1), int(raw->n1 * 3 * sizeof(float)), GL_FLOAT,
                        GL_FALSE, 0, nullptr);

  vbo.e->bind();
  glDrawElements(GL_LINES, int(raw->n2) * 2, GL_UNSIGNED_INT, nullptr);

  vbo.f->bind();
  glDrawElements(GL_TRIANGLES, int(raw->n3) * 3, GL_UNSIGNED_INT, nullptr);
}