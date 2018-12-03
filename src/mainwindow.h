#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QQuickWindow>
#include <QWindow>
#include "ccviewer.h"
#include "classification.h"

class MainWindow : public QQuickWindow {
  Q_OBJECT

  QObject* root_list;

  CCData* data;
  Classification* cls;
  CCViewer* viewer;

 public:
  MainWindow(QWindow* p = nullptr);
  Q_INVOKABLE void setData(const QString& url);
  Q_INVOKABLE void refresh();

 private:
  void addRoot(Root* r);

 private slots:
  void init();
};

#endif  // MAINWINDOW_H