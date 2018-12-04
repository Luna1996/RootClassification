#include "mainwindow.h"
#include <QTimer>
#include "ccviewer.h"

MainWindow::MainWindow(QWindow* p)
    : QQuickWindow(p), data(nullptr), cls(nullptr) {
  connect(this, &QQuickWindow::sceneGraphInitialized, this, &MainWindow::init);
}

void MainWindow::init() {
  viewer = findChild<CCViewer*>();
  root_list = findChild<QObject*>("root_list");
}

void MainWindow::setData(const QString& url) {
  if (data) delete data;
  data = CCData::LoadPLYFile(QUrl(url).toLocalFile());
  if (cls) delete cls;
  cls = new Classification(data);
  viewer->setRaw(data);
}

void MainWindow::refresh() {
  if (!cls) return;
  cls->updateContainings();
  cls->junctionAutoDetection();
  for (auto j : cls->junctions) {
    j->rgb = QVector3D(rand() % 256 / 256.f, rand() % 256 / 256.f,
                       rand() % 256 / 256.f);
    addRoot(j);
  }
  getRoots();
}

void MainWindow::addRoot(Root* r) {
  QMetaObject::invokeMethod(root_list, "append",
                            Q_ARG(QVariant, QVariant::fromValue<Sphere*>(r)));
}

QList<Sphere*>* MainWindow::getRoots() {
  QVariant r;
  QMetaObject::invokeMethod(root_list, "getRoot", Q_RETURN_ARG(QVariant, r),
                            Q_ARG(QVariant, 0));
  return nullptr;
}