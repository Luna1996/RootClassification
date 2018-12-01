#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <QSet>
#include "ccdata.h"
#include "root.h"

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

    static void addOneToIntArray(int** arr,int r, int n, int i);
    float* centerOfAFace(uint index);
    Sphere faceSet2JunctionPosition(QSet<uint>* set);
    void junctionAutoDetection (void);
    void updateContainings(void);
    int markVerticesInJunctionSpheres(void);
    void classify(void);
    int nearestSphere(QSet<uint>* set);
    void floodVerticesThroughEdgesFromSeed(uint seed);

};

#endif  // CLASSIFICATION_H
