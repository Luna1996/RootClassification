#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QQuickWindow>
#include <QWindow>
#include "ccviewer.h"
#include "classification.h"

class MainWindow : public QQuickWindow {
  Q_OBJECT

  Classification* cls;
  CCViewer* viewer;

 public:
  MainWindow(QWindow* p = nullptr);
  Q_INVOKABLE void setData(const QString& url);

 private slots:
  void init();
};

#endif  // MAINWINDOW_H