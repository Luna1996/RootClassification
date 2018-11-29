#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ccviewer.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  qmlRegisterType<CCViewer>("RCProject", 1, 0, "CCViewer");

  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:src/main.qml"));

  return app.exec();
}
