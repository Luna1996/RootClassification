#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <QSet>
#include "ccdata.h"
#include "root.h"
#include <QDebug>

class Classification {
 public:
  CCData* ccdata;
  int numJunctionDetected = 0;
  QList<Sphere> junctions;
  char* mark;

  int** edgeContaining;
  int* edgeContainingL;
  int** faceContaining;
  int* faceContainingL;
  bool* usedByEdges;

  Classification(CCData* data);
  ~Classification();

  void updateContainings(void); // 1
  void junctionAutoDetection (void); // 2
  int markVerticesInJunctionSpheres(void); // 3
  void setJunctionRadius(float r); // 4
  void classify(void); // 5
  static void addOneToIntArray(int** arr,int r, int n, int i);
  float* centerOfAFace(uint index);
  Sphere faceSet2JunctionPosition(QSet<uint>* set);
  int nearestSphere(QSet<uint>* set);
  void floodVerticesThroughEdgesFromSeed(uint seed);


};

#endif  // CLASSIFICATION_H
