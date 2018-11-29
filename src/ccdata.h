#ifndef CCDATA_H
#define CCDATA_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>

struct CCData{

    int n1, n2, n3;

    float** c1;
    int** c2;
    int** c3;

//    CCData();
    ~CCData();

    static CCData* LoadPLYFile(QString path);
    static int SaveCCData(QString path, CCData* data);
};

#endif // CCDATA_H
