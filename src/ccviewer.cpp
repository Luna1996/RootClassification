#include "ccviewer.h"
#include <math.h>
#include <QFile>
#include <QTextStream>
#include <Qt3DExtras/QSphereMesh>
#define PI 3.14159265f

CCViewer::CCViewer()
    : raw(nullptr),
      mark(nullptr),
      prog(nullptr),
      vao(0),
      vbo{0, 0, 0, 0},
      distance(10),
      center(0, 0, 0),
      eye(0, 0),
      show_center(false),
      sphere(nullptr) {
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

void CCViewer::bondProjection() {
  float w = float(width()), h = float(height());
  glViewport(int(x()), int(y()), int(w), int(h));

  float aspect = w / (h > 0 ? h : 1);
  float zNear = 10, zFar = 1e+10, fov = 70.0;
  P.setToIdentity();
  P.perspective(fov, aspect, zNear, zFar);
}

void CCViewer::bondView() {
  V.setToIdentity();
  V.lookAt(center + QVector3D(sin(eye[1] * PI / 180),
                              cos(eye[0] * PI / 180) * cos(eye[1] * PI / 180),
                              sin(eye[0] * PI / 180) * cos(eye[1] * PI / 180)) *
                        distance,
           center, QVector3D(1, 0, 0));
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

void CCViewer::init() {
  initializeOpenGLFunctions();
  connect(this, &QQuickItem::widthChanged, this, &CCViewer::bondProjection);
  connect(this, &QQuickItem::heightChanged, this, &CCViewer::bondProjection);
  QString urls[2] = {":/src/cc.vert", ":/src/cc.frag"};
  prog = loadShaderProgram(urls);
  prog->bindAttributeLocation("vertex", 0);
  prog->bindAttributeLocation("vmark", 1);
  prog->bind();

  glGenVertexArrays(1, &vao);

  bondProjection();
  bondView();
}

void CCViewer::setRaw(CCData* data) {
  raw = data;
  connect(window(), &QQuickWindow::beforeRendering, this, &CCViewer::_setRaw,
          Qt::DirectConnection);
  reconnectPaint();
  window()->update();
}

void CCViewer::_setRaw() {
  disconnect(window(), &QQuickWindow::beforeRendering, this,
             &CCViewer::_setRaw);
  auto cc = raw->flat;

  center = raw->sphere->pos;
  distance = raw->sphere->radius;

  prog->bind();

  if (glIsBuffer(vbo.v)) {
    glDeleteBuffers(1, &vbo.v);
    glDeleteBuffers(1, &vbo.e);
    glDeleteBuffers(1, &vbo.f);
  }

  if (raw) {
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo.v);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.v);
    glBufferData(GL_ARRAY_BUFFER, 3 * raw->n1 * int(sizeof(float)), cc[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vbo.e);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.e);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * raw->n2 * int(sizeof(int)), cc[1],
                 GL_STATIC_DRAW);

    glGenBuffers(1, &vbo.f);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.f);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * raw->n3 * int(sizeof(int)), cc[2],
                 GL_STATIC_DRAW);
  } else
    glDisableVertexAttribArray(0);

  bondView();
}

void CCViewer::setMark(char* m) {
  if (!raw) return;
  mark = m;
  connect(window(), &QQuickWindow::beforeRendering, this, &CCViewer::_setMark,
          Qt::DirectConnection);
  reconnectPaint();
  window()->update();
}

void CCViewer::_setMark() {
  disconnect(window(), &QQuickWindow::beforeRendering, this,
             &CCViewer::_setMark);
  prog->bind();

  if (glIsBuffer(vbo.m)) {
    glDeleteBuffers(1, &vbo.m);
  }
  if (mark) {
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo.m);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.m);
    glBufferData(GL_ARRAY_BUFFER, raw->n1, mark, GL_DYNAMIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_BYTE, 0, nullptr);
    glEnableVertexAttribArray(1);
  } else
    glDisableVertexAttribArray(1);
}

void CCViewer::clean() {}

void CCViewer::paint() {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!raw) return;

  prog->bind();

  bondProjection();
  prog->setUniformValue(prog->uniformLocation("mvp"), P * V);

  glBindVertexArray(vao);

  glPointSize(2);
  glDrawArrays(GL_POINTS, 0, int(raw->n1));

  glLineWidth(2);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.e);
  glDrawElements(GL_LINES, int(raw->n2) * 2, GL_UNSIGNED_INT, nullptr);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.f);
  glDrawElements(GL_TRIANGLES, int(raw->n3) * 3, GL_UNSIGNED_INT, nullptr);

  drawSphere(center, 5);
  //  prog->release();
  if (show_center) {
    glPointSize(3);
    glBegin(GL_LINES);
    glVertexAttribI1i(1, 0);
    glVertex3f(center[0], center[1], center[2]);
    glVertex3f(center[0] + 20, center[1], center[2]);
    glVertexAttribI1i(1, 1);
    glVertex3f(center[0], center[1], center[2]);
    glVertex3f(center[0], center[1] + 20, center[2]);
    glVertexAttribI1i(1, 2);
    glVertex3f(center[0], center[1], center[2]);
    glVertex3f(center[0], center[1], center[2] + 20);
    glEnd();
  }

  if (sphere) {
    drawSphere(sphere->pos, sphere->radius);
  }

  window()->resetOpenGLState();
}

void CCViewer::drawSphere(QVector3D& pos, float r, int lats, int longs) {
  float i, j;
  for (i = 0; i <= lats; i++) {
    float lat0 = PI * (-0.5f + (i - 1) / lats);
    float z0 = sin(lat0);
    float zr0 = cos(lat0);

    float lat1 = PI * (-0.5f + i / lats);
    float z1 = sin(lat1);
    float zr1 = cos(lat1);

    glBegin(GL_QUAD_STRIP);
    for (j = 0; j <= longs; j++) {
      float lng = 2 * PI * (j - 1) / longs;
      float x = cos(lng);
      float y = sin(lng);

      glVertex3f(x * zr0 * r + pos.x(), y * zr0 * r + pos.y(),
                 z0 * r + pos.z());
      glVertex3f(x * zr1 * r + pos.x(), y * zr1 * r + pos.y(),
                 z1 * r + pos.z());
    }
    glEnd();
  }
}