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

float* Classification::centerOfAFace(uint index){
    float* ans = new float[3];
    float x = 0, y = 0, z = 0;
    for(int i = 0;i<3;i++){
        x += this->ccdata->c1[this->ccdata->c3[index][i]][2];
        y += this->ccdata->c1[this->ccdata->c3[index][i]][3];
        z += this->ccdata->c1[this->ccdata->c3[index][i]][4];
    }
    ans[0] = x/3;
    ans[1] = y/3;
    ans[2] = z/3;

    return ans;
}

Sphere Classification::faceSet2JunctionPosition(QSet<uint>* set){
    int n = (*set).size();
    float sumX = 0;
    float sumY = 0;
    float sumZ = 0;
    foreach(const uint &value, set){
        sumX += centerOfAFace(value)[0];
        sumY += centerOfAFace(value)[1];
        sumZ += centerOfAFace(value)[2];
    }
    sumX /= n;
    sumY /= n;
    sumZ /= n;

    Sphere ans;
    ans.pos.setX(sumX);
    ans.pos.setY(sumY);
    ans.pos.setZ(sumZ);
    return ans;
}

void Classification::junctionAutoDetection (void){
    bool f;
    uint seed = 0;
    uint nF = this->ccdata->n3;
    bool* flooded = new bool[nF];
    for(uint i = 0;i<nF;i++)
        flooded[i] = false;
    flooded[seed] = true;
    QList<uint>* buffer = new QList<uint>();

    // do loop iterate until all faces are marked
    do{
        buffer->append(seed);
        QSet<uint>* facesOfThisJunction = new QSet<uint>;
        facesOfThisJunction->insert(seed);

        // do loop flooding from seed
        do{
            QSet<uint> neighbors;
            uint pf = buffer->at(0); // index of first face in the buffer
            for(int i = 0;i<3;i++){
                int v = this->ccdata->c3[pf][i]; //index of a vertex of face pf
                int k = this->faceContainingL[v];
                for(int j = 0;j<k;j++){
                    neighbors.insert(uint(this->faceContaining[j]));
                }
            }
            foreach(const uint &value, neighbors){
                if(!buffer->contains(value)){
                    buffer->append(value);
                    flooded[value] = true;
                    facesOfThisJunction->insert(value);
                }
            }

            buffer->removeFirst();

        }while(!buffer->isEmpty());

        Sphere thisJunction = faceSet2JunctionPosition(facesOfThisJunction);
        this->junctions.append(thisJunction);
        delete facesOfThisJunction;

        f = false;
        for(uint i = 0;i<nF;i++){
            if(!flooded[i]){
                f = true;
                seed = i;
                break;
            }
        }

    }while(f);

    delete buffer;
    delete[] flooded;
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

int Classification::markVerticesInJunctionSpheres(void){
    if(this->junctions.size() == 2){
        uint nV = this->ccdata->n1;
        for(uint i = 0;i<nV;i++){
            QVector3D p(this->ccdata->c1[i][2],this->ccdata->c1[i][3],this->ccdata->c1[i][4]);
            if(Sphere::inThisSphere(this->junctions.at(0),p)){
                this->mark[i] = 0;
            }
            if(Sphere::inThisSphere(this->junctions.at(1),p)){
                this->mark[i] = 1;
            }
        }
        return 0;
    }
    else{
        return 1;
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
