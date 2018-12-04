#include "classification.h"

Classification::Classification(CCData* data) {
  ccdata = data;

  uint nV = ccdata->n1;
  uint nF = ccdata->n3;
  mark = new char[nV];
  isBreakP = new bool[nV];

  edgeContaining = new int*[nV];
  edgeContainingL = new int[nV];
  edgeContainingLA = new int[nV];
  faceContaining = new int*[nV];
  faceContainingL = new int[nV];
  faceContainingLA = new int[nV];
  usedByEdges = new bool[nV];

  faceJunctionMark = new int[nF];

  for (uint i = 0; i < nV; i++) {
    mark[i] = 2;
    edgeContainingL[i] = 0;
    faceContainingL[i] = 0;
    edgeContainingLA[i] = 0;
    faceContainingLA[i] = 0;
    usedByEdges[i] = true;
    isBreakP[i] = false;
  }
}
void Classification::reset(void) {
  uint nV = ccdata->n1;
  for (uint i = 0; i < nV; i++) {
    mark[i] = 2;
    isBreakP[i] = false;
  }
  junctions.clear();
}

Classification::~Classification() {
  delete[] mark;
  //  for (uint i = 0; i < ccdata->n1; i++) {
  //    delete[] edgeContaining[i];
  //    delete[] faceContaining[i];
  //  }
  delete[] edgeContainingL;
  delete[] faceContainingL;
  delete[] edgeContainingLA;
  delete[] faceContainingLA;
  delete[] usedByEdges;
}

int Classification::addOneToIntArray(int** arr, int row, int noA, int noV,
                                     int i) {
  if (noA == 0) {
    int* newC = new int[1];
    newC[0] = i;
    arr[row] = newC;
    return 1;
  } else {
    if (noV < noA) {
      arr[row][noV] = i;
      return noA;
    } else {
      int* newC = new int[uint(noA * 2)];
      for (int j = 0; j < noV; j++) {
        newC[j] = arr[row][j];
      }
      newC[noV] = i;
      delete[] arr[row];
      arr[row] = newC;
      return noA * 2;
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

float* Classification::centerOfAFace(uint index) {
  float* ans = new float[3];
  float x = 0, y = 0, z = 0;
  for (int i = 0; i < 3; i++) {
    x += ccdata->c1[ccdata->c3[index][i]][2];
    y += ccdata->c1[ccdata->c3[index][i]][3];
    z += ccdata->c1[ccdata->c3[index][i]][4];
  }
  ans[0] = x / 3;
  ans[1] = y / 3;
  ans[2] = z / 3;

  return ans;
}

Sphere* Classification::faceSet2JunctionPosition(QSet<uint>* set) {
  int n = (*set).size();
  float sumX = 0;
  float sumY = 0;
  float sumZ = 0;
  foreach (const uint& value, (*set)) {
    sumX += centerOfAFace(value)[0];
    sumY += centerOfAFace(value)[1];
    sumZ += centerOfAFace(value)[2];
  }
  sumX /= n;
  sumY /= n;
  sumZ /= n;

  Sphere* ans = new Sphere;
  ans->pos.setX(sumX);
  ans->pos.setY(sumY);
  ans->pos.setZ(sumZ);
  return ans;
}

void Classification::junctionAutoDetection(void) {
  bool f;
  uint seed = 0;
  uint nF = ccdata->n3;
  bool* flooded = new bool[nF];
  for (uint i = 0; i < nF; i++) flooded[i] = false;
  QList<uint>* buffer = new QList<uint>();

  int junctionCount = 0;
  // do loop iterate until all faces are marked
  do {
    flooded[seed] = true;
    buffer->append(seed);
    QSet<uint>* facesOfThisJunction = new QSet<uint>;
    facesOfThisJunction->insert(seed);

    // do loop flooding from seed
    do {
      QSet<uint> neighbors;
      uint pf = buffer->at(0);  // index of first face in the buffer
      for (int i = 0; i < 3; i++) {
        int v = ccdata->c3[pf][i];  // index of a vertex of face pf
        int k = faceContainingL[v];
        for (int j = 0; j < k; j++) {
          neighbors.insert(uint(faceContaining[v][j]));
        }
      }
      foreach (const uint& value, neighbors) {
        if (!buffer->contains(value) && !flooded[value]) {
          buffer->append(value);
          flooded[value] = true;
          facesOfThisJunction->insert(value);
        }
      }

      buffer->removeFirst();

    } while (!buffer->isEmpty());

    Sphere* thisJunction = faceSet2JunctionPosition(facesOfThisJunction);
    junctions.append(thisJunction);

    // mark face of this junction in faceJunctionMark
    foreach (const uint& value, *facesOfThisJunction) {
      faceJunctionMark[value] = junctionCount;
    }
    junctionCount++;

    delete facesOfThisJunction;

    f = false;
    for (uint i = 0; i < nF; i++) {
      if (!flooded[i]) {
        f = true;
        seed = i;
        break;
      }
    }

  } while (f);

  delete buffer;
  delete[] flooded;
}

void Classification::updateContainings(void) {
  uint nE = ccdata->n2;
  uint nF = ccdata->n3;

  for (int i = 0; i < int(nE); i++) {
    //      qDebug("%d",i);
    // edge contains indices of two end points [p1 p2]
    int* edge = ccdata->c2[i];
    // p1n: edge count of p1
    int p1n = edgeContainingL[edge[0]];
    int p2n = edgeContainingL[edge[1]];
    int p1nA = edgeContainingLA[edge[0]];
    int p2nA = edgeContainingLA[edge[1]];
    /////////
    edgeContainingLA[edge[0]] =
        addOneToIntArray(edgeContaining, edge[0], p1nA, p1n, i);
    edgeContainingLA[edge[1]] =
        addOneToIntArray(edgeContaining, edge[1], p2nA, p2n, i);
    /////////
    //    edgeContaining[edge[0]][p1n] = i;
    //    edgeContaining[edge[1]][p2n] = i;
    /////////
    edgeContainingL[edge[0]]++;
    edgeContainingL[edge[1]]++;
    usedByEdges[edge[0]] = true;
    usedByEdges[edge[1]] = true;
  }

  for (int i = 0; i < int(nF); i++) {
    //      qDebug("%d",i);
    int* face = ccdata->c3[i];
    int p1n = faceContainingL[face[0]];
    int p2n = faceContainingL[face[1]];
    int p3n = faceContainingL[face[2]];
    int p1nA = faceContainingLA[face[0]];
    int p2nA = faceContainingLA[face[1]];
    int p3nA = faceContainingLA[face[2]];
    /////////
    faceContainingLA[face[0]] =
        addOneToIntArray(faceContaining, face[0], p1nA, p1n, i);
    faceContainingLA[face[1]] =
        addOneToIntArray(faceContaining, face[1], p2nA, p2n, i);
    faceContainingLA[face[2]] =
        addOneToIntArray(faceContaining, face[2], p3nA, p3n, i);
    /////////
    //    faceContaining[face[0]][p1n] = i;
    //    faceContaining[face[1]][p2n] = i;
    //    faceContaining[face[2]][p3n] = i;
    /////////
    faceContainingL[face[0]]++;
    faceContainingL[face[1]]++;
    faceContainingL[face[2]]++;
    usedByEdges[face[0]] = false;
    usedByEdges[face[1]] = false;
    usedByEdges[face[2]] = false;
  }
}

int Classification::markVerticesInJunctionSpheres(void) {
  if (junctions.size() == 2) {
    uint nV = ccdata->n1;
    for (uint i = 0; i < nV; i++) {
      QVector3D p(ccdata->c1[i][2], ccdata->c1[i][3], ccdata->c1[i][4]);
      if (Sphere::inThisSphere(junctions.at(0), p)) {
        mark[i] = 0;
      }
      if (Sphere::inThisSphere(junctions.at(1), p)) {
        mark[i] = 1;
      }
    }
    return 0;
  } else {
    return 1;
  }
}

// void Classification::classify(void) {
//  uint nV = ccdata->n1;
//  uint hnV = nV / 2;
//  for (uint i = 0; i < nV; i++) {
//    if (i < hnV) {
//      mark[i] = 0;
//    } else {
//      mark[i] = 1;
//    }
//  }
//}

void Classification::classify(void) {
  uint nV = ccdata->n1;
  //  // end points list
  //  QList<uint> endPoints;
  //  for(uint i = 0;i<nV;i++){
  //      if(usedByEdges[i] && (edgeContainingL[i] == 1) &&
  //      mark[i] == 2){
  //          endPoints.append(i);
  //      }
  //  }
  //  // emurate all end points
  //  uint nep = uint(endPoints.size());
  //  for(uint i = 0;i < nep;i++){
  //    floodVerticesThroughEdgesFromSeed(endPoints.at(0));
  //  }

  // line segments with no end
  while (true) {
    bool someVerticesNotClassified = false;
    uint seed = 0;
    for (uint i = 0; i < nV; i++) {
      if (mark[i] == 2) {
        someVerticesNotClassified = true;
        seed = i;
        break;
      }
    }
    if (!someVerticesNotClassified) {
      break;
    }
    floodVerticesThroughEdgesFromSeed(seed);
  }
}

void Classification::floodVerticesThroughEdgesFromSeed(uint seed) {
  // start this seed point
  QSet<uint> floodedThisSeed;
  floodedThisSeed.insert(seed);

  QList<uint> buffer;
  buffer.append(seed);

  int assignment = 2;  // result of classification

  while (!buffer.isEmpty()) {
    uint v = buffer.at(0);
    int* contained = edgeContaining[v];
    uint containedN = uint(edgeContainingL[v]);

    QSet<uint> neighbors;
    // insert all endpoints of related edges containing v to neighbor set
    for (uint j = 0; j < containedN; j++) {
      uint edgeThisIndex = uint(contained[j]);
      uint p1 = uint(ccdata->c2[edgeThisIndex][0]);
      uint p2 = uint(ccdata->c2[edgeThisIndex][1]);
      if (!isBreakP[p1]) neighbors.insert(p1);
      if (!isBreakP[p2]) neighbors.insert(p2);
    }
    // add elements in set into buffer
    foreach (const uint& value, neighbors) {
      bool insideSphere = false;
      // check whether this point a in any sphere
      QVector3D vp(ccdata->c1[value][2], ccdata->c1[value][3],
                   ccdata->c1[value][4]);
      // check sphere 1
      if (Sphere::inThisSphere(junctions.at(0), vp)) {
        insideSphere = true;
        if (assignment == 2) {
          assignment = 3;
        } else if (assignment == 4) {
          assignment = 5;
        }
      }
      // check sphere 2
      if (Sphere::inThisSphere(junctions.at(1), vp)) {
        insideSphere = true;
        if (assignment == 2) {
          assignment = 4;
        } else if (assignment == 3) {
          assignment = 5;
        }
      }
      // not in any sphere
      if (!insideSphere) {
        if (!buffer.contains(value) && !floodedThisSeed.contains(value)) {
          buffer.append(value);
          floodedThisSeed.insert(value);
        }
      }
    }
    // remove first element in buffer
    buffer.removeFirst();
  }
  if (assignment == 3) {
    foreach (const uint& value, floodedThisSeed) { mark[value] = 0; }
  }
  if (assignment == 4) {
    foreach (const uint& value, floodedThisSeed) { mark[value] = 1; }
  }
  if (assignment == 2 || assignment == 5) {
    int nearest = nearestSphere(&floodedThisSeed);
    foreach (const uint& value, floodedThisSeed) {
      mark[value] = char(nearest);
    }
  }

  // finish this end point
}

int Classification::nearestSphere(QSet<uint>* set) {
  float xC = 0;
  float yC = 0;
  float zC = 0;
  int np = (*set).size();
  foreach (const uint& value, *set) {
    xC += ccdata->c1[value][2];
    yC += ccdata->c1[value][3];
    zC += ccdata->c1[value][4];
  }
  xC /= np;
  yC /= np;
  zC /= np;

  QVector3D center(xC, yC, zC);
  float d1 = junctions.at(0)->pos.distanceToPoint(center);
  float d2 = junctions.at(1)->pos.distanceToPoint(center);

  if (d1 < d2) {
    return 0;
  } else {
    return 1;
  }
}

void Classification::setJunctionRadius(float r) {
  if (junctions.size() == 2 | junctions.size() == 0) {
    Sphere* j1 = junctions.at(0);
    Sphere* j2 = junctions.at(1);
    float d = j1->pos.distanceToPoint(j2->pos);
    j1->radius = d * r;
    j2->radius = d * r;
    junctions.clear();
    junctions.append(j1);
    junctions.append(j2);
  } else {
    qDebug() << "Illegal number of junction:" << junctions.size();
  }
}

void Classification::setBreakPoints(QList<uint>* brks) {
  QList<uint>::iterator i;
  for (i = brks->begin(); i != brks->end(); ++i) isBreakP[*i] = true;
}
