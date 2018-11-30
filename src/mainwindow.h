#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QQuickWindow>
#include <QWindow>

class MainWindow : public QQuickWindow {
  Q_OBJECT

 public:
  MainWindow(QWindow* p = nullptr);

 private slots:
  void br() { qInfo("1"); }
  void bs() { qInfo("2"); }
  void ar() { qInfo("3"); }
  void as() { qInfo("4"); }
  void inv() { qInfo("5"); }
  void init() { qInfo("6"); }
};

#endif  // MAINWINDOW_H