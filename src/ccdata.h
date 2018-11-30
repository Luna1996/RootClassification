#ifndef CCDATA_H
#define CCDATA_H

#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include "root.h"

struct CCData {
  uint n1, n2, n3;

  float** c1;
  int** c2;
  int** c3;

  void** flat;
  Sphere* sphere;

  ~CCData();

  static CCData* LoadPLYFile(QString path);
  static int SaveCCData(QString path, CCData* data);
};

#endif  // CCDATA_H
