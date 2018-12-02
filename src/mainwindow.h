#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QQuickWindow>
#include <QWindow>
#include "ccviewer.h"
#include "classification.h"

class MainWindow : public QQuickWindow {
  Q_OBJECT

  CCData* current;
  Classification* cls;
  CCViewer* viewer;

 public:
  MainWindow(QWindow* p = nullptr);

 private slots:
  void init();
};

#endif  // MAINWINDOW_H