#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ccviewer.h"
#include "ccdata.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  qmlRegisterType<CCViewer>("RCProject", 1, 0, "CCViewer");

  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:src/main.qml"));
  //

  QString path1 = "D:/Assi/WUSTL/CSE 554A/FP/TwoRoots/Skeletons/p0007d07_skelSmoothed2.ply";
  CCData* cc = CCData::LoadPLYFile(path1);

  QString path2 = "D:/Assi/WUSTL/CSE 554A/FP/TwoRoots/writefiletest/output.ply";
  int a = CCData::SaveCCData(path2, cc);




  //

  return app.exec();
}
