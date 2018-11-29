#ifndef CCVIEWER_H
#define CCVIEWER_H
#include <QOpenGLFunctions_3_0>
#include <QQuickItem>
#include <QQuickWindow>

class CCViewer : public QQuickItem, protected QOpenGLFunctions_3_0 {
  Q_OBJECT
 public:
  CCViewer();
  ~CCViewer();

 public slots:
  void onWindowChanged(QQuickWindow* win);
  void sync();
  void paint();
};

#endif  // CCVIEWER_H