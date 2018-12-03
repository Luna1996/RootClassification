#include "mainwindow.h"
#include <QTimer>
#include "ccviewer.h"

MainWindow::MainWindow(QWindow* p) : QQuickWindow(p), cls(nullptr) {
  connect(this, &QQuickWindow::sceneGraphInitialized, this, &MainWindow::init);
}

void MainWindow::init() { viewer = findChild<CCViewer*>(); }

void MainWindow::setData(const QString& url) {
  CCData* d = CCData::LoadPLYFile(QUrl(url).toLocalFile());
  if (cls) delete cls;
  cls = new Classification(d);
  viewer->setRaw(d);
}