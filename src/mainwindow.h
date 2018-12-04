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
  Q_INVOKABLE void setSphere(float, float, float, float, float, float, float);
  Q_INVOKABLE void runAlgorithm(float x1, float y1, float z1, float x2,
                                float y2, float z2, float r1, float g1,
                                float b1, float r2, float g2, float b2,
                                float d1, float d2);

 private:
  void addRoot(Root* r);

 private slots:
  void init();
};

#endif  // MAINWINDOW_H