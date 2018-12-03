#include "classification.h"

Classification::Classification(CCData* data) {
  this->ccdata = data;



  uint nV = this->ccdata->n1;
  uint nF = this->ccdata->n3;
  this->mark = new char[nV];
  this->isBreakP = new bool[nV];

  this->edgeContaining = new int*[nV];
  this->edgeContainingL = new int[nV];
  this->edgeContainingLA = new int[nV];
  this->faceContaining = new int*[nV];
  this->faceContainingL = new int[nV];
  this->faceContainingLA = new int[nV];
  this->usedByEdges = new bool[nV];

  this->faceJunctionMark = new int[nF];

  for (uint i = 0; i < nV; i++) {
    this->mark[i] = 2;
    this->edgeContainingL[i] = 0;
    this->faceContainingL[i] = 0;
    this->edgeContainingLA[i] = 0;
    this->faceContainingLA[i] = 0;
    this->usedByEdges[i] = true;
    this->isBreakP[i] = false;
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
  delete[] this->edgeContainingLA;
  delete[] this->faceContainingLA;
  delete[] this->usedByEdges;
}

int Classification::addOneToIntArray(int** arr, int row, int noA, int noV, int i) {
    if(noA == 0){
        int* newC = new int[1];
        newC[0] = i;
        arr[row] = newC;
        return 1;
    }
    else{
        if(noV < noA){
            arr[row][noV] = i;
            return noA;
        }
        else{
            int* newC = new int[uint(noA*2)];
            for (int j = 0; j < noV; j++) {
                newC[j] = arr[row][j];
            }
            newC[noV] = i;
            delete[] arr[row];
            arr[row] = newC;
            return noA*2;
        }
    }
//  int* newC = new int[uint(n) + 1];
//  for (int j = 0; j < n; j++) {
//    newC[j] = arr[row][j];
//  }
//  newC[n] = i;
//  if(n != 0){
//      delete[] arr[row];
//  }
//  arr[r] = newC;
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
    foreach(const uint &value, (*set)){
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
    QList<uint>* buffer = new QList<uint>();

    int junctionCount = 0;
    // do loop iterate until all faces are marked
    do{
        flooded[seed] = true;
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
                    neighbors.insert(uint(this->faceContaining[v][j]));
                }
            }
            foreach(const uint &value, neighbors){
                if(!buffer->contains(value) && !flooded[value]){
                    buffer->append(value);
                    flooded[value] = true;
                    facesOfThisJunction->insert(value);
                }
            }

            buffer->removeFirst();

        }while(!buffer->isEmpty());

        Sphere thisJunction = faceSet2JunctionPosition(facesOfThisJunction);
        this->junctions.append(thisJunction);

        //mark face of this junction in faceJunctionMark
        foreach(const uint &value, *facesOfThisJunction){
            this->faceJunctionMark[value] = junctionCount;
        }
        junctionCount ++;

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
//      qDebug("%d",i);
    // edge contains indices of two end points [p1 p2]
    int* edge = this->ccdata->c2[i];
    // p1n: edge count of p1
    int p1n = this->edgeContainingL[edge[0]];
    int p2n = this->edgeContainingL[edge[1]];
    int p1nA = this->edgeContainingLA[edge[0]];
    int p2nA = this->edgeContainingLA[edge[1]];
    /////////
    this->edgeContainingLA[edge[0]] =  addOneToIntArray(edgeContaining, edge[0], p1nA, p1n, i);
    this->edgeContainingLA[edge[1]] = addOneToIntArray(edgeContaining, edge[1], p2nA, p2n, i);
    /////////
//    edgeContaining[edge[0]][p1n] = i;
//    edgeContaining[edge[1]][p2n] = i;
    /////////
    this->edgeContainingL[edge[0]]++;
    this->edgeContainingL[edge[1]]++;
    this->usedByEdges[edge[0]] = true;
    this->usedByEdges[edge[1]] = true;
  }

  for (int i = 0; i < int(nF); i++) {
//      qDebug("%d",i);
    int* face = this->ccdata->c3[i];
    int p1n = this->faceContainingL[face[0]];
    int p2n = this->faceContainingL[face[1]];
    int p3n = this->faceContainingL[face[2]];
    int p1nA = this->faceContainingLA[face[0]];
    int p2nA = this->faceContainingLA[face[1]];
    int p3nA = this->faceContainingLA[face[2]];
    /////////
    this->faceContainingLA[face[0]] = addOneToIntArray(faceContaining, face[0], p1nA, p1n, i);
    this->faceContainingLA[face[1]] = addOneToIntArray(faceContaining, face[1], p2nA, p2n, i);
    this->faceContainingLA[face[2]] = addOneToIntArray(faceContaining, face[2], p3nA, p3n, i);
    /////////
//    faceContaining[face[0]][p1n] = i;
//    faceContaining[face[1]][p2n] = i;
//    faceContaining[face[2]][p3n] = i;
    /////////
    this->faceContainingL[face[0]]++;
    this->faceContainingL[face[1]]++;
    this->faceContainingL[face[2]]++;
    this->usedByEdges[face[0]] = false;
    this->usedByEdges[face[1]] = false;
    this->usedByEdges[face[2]] = false;
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

//void Classification::classify(void) {
//  uint nV = this->ccdata->n1;
//  uint hnV = nV / 2;
//  for (uint i = 0; i < nV; i++) {
//    if (i < hnV) {
//      this->mark[i] = 0;
//    } else {
//      this->mark[i] = 1;
//    }
//  }
//}

void Classification::classify(void) {
    uint nV = this->ccdata->n1;
//  // end points list
//  QList<uint> endPoints;
//  for(uint i = 0;i<nV;i++){
//      if(this->usedByEdges[i] && (this->edgeContainingL[i] == 1) && this->mark[i] == 2){
//          endPoints.append(i);
//      }
//  }
//  // emurate all end points
//  uint nep = uint(endPoints.size());
//  for(uint i = 0;i < nep;i++){
//    floodVerticesThroughEdgesFromSeed(endPoints.at(0));
//  }

  // line segments with no end
  while(true){
      bool someVerticesNotClassified = false;
      uint seed = 0;
      for(uint i = 0;i<nV;i++){
          if(this->mark[i] == 2){
              someVerticesNotClassified = true;
              seed = i;
              break;
          }
      }
      if(!someVerticesNotClassified){
          break;
      }
      floodVerticesThroughEdgesFromSeed(seed);
  }
}

void Classification::floodVerticesThroughEdgesFromSeed(uint seed){
    //start this seed point
    QSet<uint> floodedThisSeed;
    floodedThisSeed.insert(seed);

    QList<uint> buffer;
    buffer.append(seed);

    int assignment = 2; // result of classification

    while(!buffer.isEmpty()){
        uint v = buffer.at(0);
        int* contained = this->edgeContaining[v];
        uint containedN = uint(this->edgeContainingL[v]);

        QSet<uint> neighbors;
        //insert all endpoints of related edges containing v to neighbor set
        for(uint j = 0;j<containedN;j++){
            uint edgeThisIndex = uint(contained[j]);
            uint p1 = uint(this->ccdata->c2[edgeThisIndex][0]);
            uint p2 = uint(this->ccdata->c2[edgeThisIndex][1]);
            if(!this->isBreakP[p1])
                neighbors.insert(p1);
            if(!this->isBreakP[p2])
                neighbors.insert(p2);
        }
        // add elements in set into buffer
        foreach(const uint &value, neighbors){
            bool insideSphere = false;
            //check whether this point a in any sphere
            QVector3D vp(this->ccdata->c1[value][2],this->ccdata->c1[value][3],this->ccdata->c1[value][4]);
            // check sphere 1
            if(Sphere::inThisSphere(this->junctions.at(0),vp)){
                insideSphere = true;
                if(assignment == 2){
                    assignment = 3;
                }else if(assignment == 4){
                    assignment = 5;
                }
            }
            // check sphere 2
            if(Sphere::inThisSphere(this->junctions.at(1),vp)){
                insideSphere = true;
                if(assignment == 2){
                    assignment = 4;
                }else if(assignment == 3){
                    assignment = 5;
                }
            }
            // not in any sphere
            if(!insideSphere){
                if(!buffer.contains(value) && !floodedThisSeed.contains(value)){
                    buffer.append(value);
                    floodedThisSeed.insert(value);
                }
            }
        }
        //remove first element in buffer
        buffer.removeFirst();
    }
    if(assignment == 3){
        foreach(const uint &value, floodedThisSeed){
            this->mark[value] = 0;
        }
    }
    if(assignment == 4){
        foreach(const uint &value, floodedThisSeed){
            this->mark[value] = 1;
        }
    }
    if(assignment == 2 || assignment == 5){
        int nearest = this->nearestSphere(&floodedThisSeed);
        foreach(const uint &value, floodedThisSeed){
            this->mark[value] = char(nearest);
        }
    }

    //finish this end point
}

int Classification::nearestSphere(QSet<uint>* set){
    float xC = 0;
    float yC = 0;
    float zC = 0;
    int np = (*set).size();
    foreach(const uint &value, *set){
        xC += this->ccdata->c1[value][2];
        yC += this->ccdata->c1[value][3];
        zC += this->ccdata->c1[value][4];
    }
    xC /= np;
    yC /= np;
    zC /= np;

    QVector3D center(xC, yC, zC);
    float d1 = this->junctions.at(0).pos.distanceToPoint(center);
    float d2 = this->junctions.at(1).pos.distanceToPoint(center);

    if(d1<d2){
        return 0;
    }
    else{
        return 1;
    }
}

void Classification::setJunctionRadius(float r){
    if(this->junctions.size() == 2){
        Sphere j1 = junctions.at(0);
        Sphere j2 = junctions.at(1);
        float d = j1.pos.distanceToPoint(j2.pos);
        j1.radius = d*r;
        j2.radius = d*r;
        this->junctions.clear();
        this->junctions.append(j1);
        this->junctions.append(j2);
    }
    else{
        qDebug() << "Illegal number of junction:" << this->junctions.size();
    }
}

void Classification::setBreakPoints(QList<uint> *brks){
    QList<uint>::iterator i;
    for (i = brks->begin(); i != brks->end(); ++i)
       this->isBreakP[*i] = true;
}








