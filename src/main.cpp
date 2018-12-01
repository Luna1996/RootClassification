#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ccdata.h"
#include "ccviewer.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  qmlRegisterType<MainWindow>("RCProject", 1, 0, "RCWindow");
  qmlRegisterType<CCViewer>("RCProject", 1, 0, "CCViewer");
  qmlRegisterRevision<QWindow, 1>("RCProject", 1, 0);
  qmlRegisterRevision<QQuickWindow, 1>("RCProject", 1, 0);

  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:src/main.qml"));
  return app.exec();
}
