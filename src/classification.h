#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <QSet>
#include "ccdata.h"
#include "root.h"
#include <QDebug>

class Classification {
 public:
  CCData* ccdata;
  QList<Sphere> junctions;
  char* mark;
  bool* isBreakP;

  int** edgeContaining;
  int* edgeContainingL;
  int* edgeContainingLA;
  int** faceContaining;
  int* faceContainingL;
  int* faceContainingLA;
  bool* usedByEdges;

  int* faceJunctionMark;

  Classification(CCData* data);
  ~Classification();

  void updateContainings(void); // 1
  void junctionAutoDetection (void); // 2
  int markVerticesInJunctionSpheres(void); // 3
  void setJunctionRadius(float r); // 4
  void classify(void); // 5
  void setBreakPoints(QList<uint> *brks); // 6
  void reset(void);


  static int addOneToIntArray(int** arr,int row, int noA, int noV, int i);
  float* centerOfAFace(uint index);
  Sphere faceSet2JunctionPosition(QSet<uint>* set);
  int nearestSphere(QSet<uint>* set);
  void floodVerticesThroughEdgesFromSeed(uint seed);



};

#endif  // CLASSIFICATION_H
