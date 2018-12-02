#include "mainwindow.h"
#include <QTimer>
#include "ccviewer.h"

MainWindow::MainWindow(QWindow* p) : QQuickWindow(p), current(nullptr) {
  connect(this, &QQuickWindow::beforeRendering, this, &MainWindow::init,
          Qt::DirectConnection);
  current = CCData::LoadPLYFile(":/dat/1.ply");
}

void MainWindow::init() {
  disconnect(this, &QQuickWindow::beforeRendering, this, &MainWindow::init);
  viewer = findChild<CCViewer*>();
  viewer->setRaw(current);
  return;
}
