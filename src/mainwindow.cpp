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
  QTimer::singleShot(0, [&]() { cls->updateContainings(); });
}

void MainWindow::refresh() {
  if (!cls) return;
  cls->junctionAutoDetection();
  for (auto j : cls->junctions) {
    j->rgb = QVector3D(rand() % 256 / 256.f, rand() % 256 / 256.f,
                       rand() % 256 / 256.f);
    j->radius = 20;
    addRoot(j);
  }
}

void MainWindow::setSphere(float r, float g, float b, float x, float y, float z,
                           float d) {
  if (viewer->sphere) delete viewer->sphere;
  viewer->sphere = new Sphere;
  viewer->sphere->rgb = QVector3D(r, g, b);
  viewer->sphere->pos = QVector3D(x, y, z);
  viewer->sphere->radius = d;
  update();
}

void MainWindow::addRoot(Root* r) {
  QMetaObject::invokeMethod(root_list, "append",
                            Q_ARG(QVariant, QVariant::fromValue<Sphere*>(r)));
}

void MainWindow::runAlgorithm(float x1, float y1, float z1, float x2, float y2,
                              float z2, float r1, float g1, float b1, float r2,
                              float g2, float b2, float d1, float d2) {
  cls->junctions.clear();
  Sphere* j1 = new Sphere();
  Sphere* j2 = new Sphere();

  j1->pos = QVector3D(x1, y1, z1);
  j2->pos = QVector3D(x2, y2, z2);
  j1->rgb = QVector3D(r1, g1, b1);
  j2->rgb = QVector3D(r2, g2, b2);
  j1->radius = d1;
  j2->radius = d2;

  cls->junctions.append(j1);
  cls->junctions.append(j2);

  cls->markVerticesInJunctionSpheres();
  cls->setJunctionRadius(0.25);
  qDebug("%f,%f",cls->junctions.at(0)->radius, cls->junctions.at(1)->radius);
  cls->classify();
  viewer->setMark(cls->mark, j1->rgb, j2->rgb);
}
