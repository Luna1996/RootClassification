#ifndef CCDATA_H
#define CCDATA_H

#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>

struct CCData {
  uint n1, n2, n3;

  float** c1;
  int** c2;
  int** c3;

  //    CCData();
  ~CCData();

  static CCData* LoadPLYFile(QString path);
  static int SaveCCData(QString path, CCData* data);
  void** flatten(void);
};

#endif  // CCDATA_H
