#include "ccviewer.h"

CCViewer::CCViewer() {
  connect(this, &QQuickItem::windowChanged, this, &CCViewer::onWindowChanged);
}

CCViewer::~CCViewer() {
  disconnect(window(), &QQuickWindow::beforeRendering, this, &CCViewer::paint);
}

void CCViewer::onWindowChanged(QQuickWindow* win) {
  if (win) {
    connect(window(), &QQuickWindow::beforeSynchronizing, this, &CCViewer::sync,
            Qt::DirectConnection);
    win->setClearBeforeRendering(false);
  }
}

void CCViewer::sync() {
  connect(window(), &QQuickWindow::beforeRendering, this, &CCViewer::paint,
          Qt::DirectConnection);
  qInfo("sync");
  initializeOpenGLFunctions();
}

void CCViewer::paint() {
  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}