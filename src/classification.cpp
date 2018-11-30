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
}

Classification::~Classification() {
  delete[] this->mark;
  for (uint i = 0; i < this->ccdata->n1; i++) {
    delete[] this->edgeContaining[i];
    delete[] this->faceContaining[i];
  }
  delete[] this->edgeContainingL;
  delete[] this->faceContainingL;
}

void Classification::updateContainings(void) {}

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
