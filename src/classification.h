#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include "ccdata.h"
#include "root.h"

class Classification {
 public:
  CCData* ccdata;
  int numRootDetected = 0;
  QList<Root> roots;
  char* mark;

  int** edgeContaining;
  int* edgeContainingL;
  int** faceContaining;
  int* faceContainingL;

  Classification(CCData* data);
  ~Classification();

  void updateContainings(void);
  void markInSpheres(void);
  void classify(void);
};

#endif  // CLASSIFICATION_H