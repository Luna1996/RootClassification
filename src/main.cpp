#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ccdata.h"
#include "ccviewer.h"
#include "classification.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  qmlRegisterType<MainWindow>("RCProject", 1, 0, "RCWindow");
  qmlRegisterType<CCViewer>("RCProject", 1, 0, "CCViewer");
  qmlRegisterRevision<QWindow, 1>("RCProject", 1, 0);
  qmlRegisterRevision<QQuickWindow, 1>("RCProject", 1, 0);

  //
  CCData* cc = CCData::LoadPLYFile("D:/WORK/GitHub/RootClassification/dat/test.ply");
  cc->flatten();
  Classification cls(cc);
  cls.updateContainings();
  for(uint i = 0;i<cc->n1;i++){
      qDebug("Point %d: ",i);
      qDebug("Edge: ");
      for(int j = 0;j<cls.edgeContainingL[i];j++){
          qDebug("%d ", cls.edgeContaining[i][j]);
      }
      qDebug("Face: ");
      for(int j = 0;j<cls.faceContainingL[i];j++){
          qDebug("%d ", cls.faceContaining[i][j]);
      }
  }
  cls.junctionAutoDetection();
  qDebug() << cls.junctions[0].pos;
  qDebug() << cls.junctions[1].pos;

  // set radius to 1/4
  cls.setJunctionRadius(0.25);
  qDebug() << cls.junctions[0].radius;
  qDebug() << cls.junctions[1].radius;
  //

  //mark points in spheres
  cls.markVerticesInJunctionSpheres();
  cls.classify();

  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:src/main.qml"));
  return app.exec();
}
