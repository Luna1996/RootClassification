#include "mainwindow.h"
#include <QTimer>
#include "ccviewer.h"

MainWindow::MainWindow(QWindow* p) : QQuickWindow(p), current(nullptr) {
  connect(this, &QQuickWindow::beforeRendering, this, &MainWindow::init,
          Qt::DirectConnection);
  current = CCData::LoadPLYFile(":/dat/2.ply");
  cls = new Classification(current);
  cls->updateContainings();
  cls->junctionAutoDetection();
  for(int i = 0;i<this->cls->junctions.size();i++)
  qDebug() << cls->junctions[i].pos;

  cls->junctions.removeAt(2);
  cls->setJunctionRadius(0.25);
  cls->markVerticesInJunctionSpheres();
  cls->classify();
}

void MainWindow::init() {
  disconnect(this, &QQuickWindow::beforeRendering, this, &MainWindow::init);
  viewer = findChild<CCViewer*>();
  viewer->setRaw(current);
//  char* m = new char[current->n1];
//  for (uint i = 0; i < current->n1; i++) m[i] = rand() % 2;
//  viewer->setMark(m);
  viewer->setMark(cls->mark);
  return;
}
