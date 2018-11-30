#include "classification.h"

Classification::Classification(CCData* data) {
  this->ccdata = data;

  this->mark = new char[this->ccdata->n1];

  uint nV = this->ccdata->n1;
  for (uint i = 0; i < nV; i++) {
    this->mark[i] = 2;
  }

  this->edgeContaining = new int*[nV];
  this->edgeContainingL = new int[nV];
  this->faceContaining = new int*[nV];
  this->faceContainingL = new int[nV];
  this->usedByEdges = new bool[nV];
  for (uint i = 0; i < nV; i++) {
    this->edgeContainingL[i] = 0;
    this->faceContainingL[i] = 0;
    this->usedByEdges[i] = true;
  }
}

Classification::~Classification() {
  delete[] this->mark;
  for (uint i = 0; i < this->ccdata->n1; i++) {
    delete[] this->edgeContaining[i];
    delete[] this->faceContaining[i];
  }
  delete[] this->edgeContainingL;
  delete[] this->faceContainingL;
  delete[] this->usedByEdges;
}

void Classification::addOneToIntArray(int** arr, int r, int n, int i) {
  int* newC = new int[uint(n) + 1];
  for (int j = 0; j < n; j++) {
    newC[j] = arr[r][j];
  }
  newC[n] = i;
  delete[] arr[r];
  arr[r] = newC;
}

void Classification::updateContainings(void) {
  uint nE = this->ccdata->n2;
  uint nF = this->ccdata->n3;

  for (int i = 0; i < int(nE); i++) {
    // edge contains indices of two end points [p1 p2]
    int* edge = this->ccdata->c2[i];
    // p1n: edge count of p1
    int p1n = this->edgeContainingL[edge[0]];
    int p2n = this->edgeContainingL[edge[1]];
    /////////
    addOneToIntArray(edgeContaining, edge[0], p1n, i);
    addOneToIntArray(edgeContaining, edge[1], p2n, i);
    /////////
    this->edgeContainingL[edge[0]]++;
    this->edgeContainingL[edge[1]]++;
    usedByEdges[edge[0]] = true;
    usedByEdges[edge[1]] = true;
  }

  for (int i = 0; i < int(nF); i++) {
    int* face = this->ccdata->c3[i];
    int p1n = this->faceContainingL[face[0]];
    int p2n = this->faceContainingL[face[1]];
    int p3n = this->faceContainingL[face[2]];
    /////////
    addOneToIntArray(faceContaining, face[0], p1n, i);
    addOneToIntArray(faceContaining, face[1], p2n, i);
    addOneToIntArray(faceContaining, face[2], p3n, i);
    /////////
    this->faceContainingL[face[0]]++;
    this->faceContainingL[face[1]]++;
    this->faceContainingL[face[2]]++;
    usedByEdges[face[0]] = false;
    usedByEdges[face[1]] = false;
    usedByEdges[face[2]] = false;
  }
}

void Classification::classify(void) {
  uint nV = this->ccdata->n1;
  uint hnV = nV / 2;
  for (uint i = 0; i < nV; i++) {
    if (i < hnV) {
      this->mark[i] = 0;
    } else {
      this->mark[i] = 1;
    }
  }
}
