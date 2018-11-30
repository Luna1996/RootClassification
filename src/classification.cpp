#include "classification.h"

Classification::Classification(CCData* data)
{
    this->ccdata = data;

    this->mark = new char[this->ccdata->n1];

    int nV = this->ccdata->n1;
    for(int i = 0;i<nV;i++){
        this->mark[i] = 2;
    }

    this->edgeContaining = new int*[nV];
    this->edgeContainingL = new int[nV];
    this->faceContaining = new int*[nV];
    this->faceContainingL = new int[nV];
}

void Classification::classify(void){
    int nV = this->ccdata->n1;
    int hnV = nV/2;
    for(int i = 0;i<nV;i++){
        if(i<hnV){
            this->mark[i] = 0;
        }
        else{
            this->mark[i] = 1;
        }
    }
}
