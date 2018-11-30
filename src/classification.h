#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include "ccdata.h"
#include "root.h"

class Classification
{
public:
    CCData* ccdata;
    int numRootDetected = 0;
    QList<Root> roots;
    char* mark;

    int** edgeContaining;
    int* edgeContainingL;
    int** faceContaining;
    int* faceContainingL;
    bool* usedByEdges;

    Classification(CCData* data);
    ~Classification();

    static void addOneToIntArray(int** arr,int r, int n, int i);
    void junctionAutoDetection (void);
    void updateContainings(void);
    void markInSpheres(void);
    void classify(void);

};

#endif // CLASSIFICATION_H
