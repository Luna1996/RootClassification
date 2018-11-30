#include "ccviewer.h"
#include <QFile>
#include <QTextStream>

CCViewer::CCViewer()
    : raw(nullptr),
      mark(nullptr),
      prog(nullptr),
      vao(0),
      vbo{0, 0, 0, 0},
      eye(1, 1, 1) {
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
  float zNear = 0, zFar = distance, fov = 70.0;
  P.setToIdentity();
  P.perspective(fov, aspect, zNear, zFar);
  P.lookAt(center, eye * distance, QVector3D(0, 1, 0));
}

void CCViewer::init() {
  initializeOpenGLFunctions();
  QString urls[2] = {":/src/cc.vert", ":/src/cc.frag"};
  prog = loadShaderProgram(urls);
  prog->bindAttributeLocation("vertex", 0);
  prog->bindAttributeLocation("vmark", 1);
  prog->bind();

  glGenVertexArrays(1, &vao);
  GLuint buf[4];
  glGenBuffers(4, buf);
  vbo = {buf[0], buf[1], buf[2], buf[3]};

  prog->release();
}

void CCViewer::setRaw(CCData* data) {
  raw = data;
  auto cc = data->flat;

  center = raw->sphere->pos;
  distance = raw->sphere->radius;

  prog->bind();

  if (data) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.v);
    glBufferData(GL_ARRAY_BUFFER, 3 * raw->n1 * int(sizeof(float)), cc[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.e);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * raw->n2 * int(sizeof(int)), cc[1],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.f);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * raw->n3 * int(sizeof(int)), cc[2],
                 GL_STATIC_DRAW);
  } else
    glDisableVertexAttribArray(0);
  update();
}

void CCViewer::setMark(char* m) {
  if (!raw) return;
  mark = m;

  prog->bind();

  if (m) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.m);
    glBufferData(GL_ARRAY_BUFFER, raw->n1 * int(sizeof(char)), m,
                 GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);
  } else
    glDisableVertexAttribArray(1);
  update();
}

void CCViewer::clean() {}

void CCViewer::paint() {
  glClearColor(1, 1, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!raw) return;

  prog->bind();

  resizeGL();
  prog->setUniformValue(prog->uniformLocation("mvp"), P);

  glBindVertexArray(vao);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.e);
  glDrawElements(GL_LINES, int(raw->n2) * 2, GL_UNSIGNED_INT, nullptr);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.f);
  glDrawElements(GL_TRIANGLES, int(raw->n3) * 3, GL_UNSIGNED_INT, nullptr);

  window()->resetOpenGLState();
}