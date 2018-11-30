#include "ccdata.h"

CCData::~CCData() {
  delete[] c1;
  delete[] c2;
  delete[] c3;
}

CCData* CCData::LoadPLYFile(QString path) {
  uint numV, numE, numF;

  uint nfV = 5;
  uint nfE = 2;
  uint nfF = 4;

  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return nullptr;

  QTextStream in(&file);

  int headerLength = 14;
  QString header[14];
  for (int i = 0; i < headerLength; i++) {
    header[i] = in.readLine();
  }

  // extract number of vertex
  numV = uint(header[2].split(" ").at(2).toInt());

  // extract number of edge
  numE = uint(header[8].split(" ").at(2).toInt());

  // extract number of face
  numF = uint(header[11].split(" ").at(2).toInt());

  float** v = new float*[numV];
  int** e = new int*[numE];
  int** f = new int*[numF];

  // v
  for (uint i = 0; i < numV; i++) {
    QStringList vL = in.readLine().split(" ");
    v[i] = new float[nfV];
    for (int j = 0; j < int(nfV); j++) {
      v[i][j] = vL.at(j).toFloat();
    }
  }
  // e
  for (uint i = 0; i < numE; i++) {
    QStringList eL = in.readLine().split(" ");
    e[i] = new int[nfE];
    for (int j = 0; j < int(nfE); j++) {
      e[i][j] = eL.at(j).toInt();
    }
  }

  // f
  for (uint i = 0; i < numF; i++) {
    QStringList fL = in.readLine().split(" ");
    f[i] = new int[nfF - 1];
    for (int j = 1; j < int(nfF); j++) {
      // effective data start from second field
      f[i][j - 1] = fL.at(j).toInt();
    }
  }

  CCData* ans = new CCData;
  ans->n1 = numV;
  ans->n2 = numE;
  ans->n3 = numF;
  ans->c1 = v;
  ans->c2 = e;
  ans->c3 = f;

  return ans;
}

int CCData::SaveCCData(QString path, CCData* cc) {
  QFile file(path);
  if (file.open(QFile::WriteOnly | QFile::Truncate)) {
    QTextStream out(&file);

    uint nV = cc->n1;
    uint nE = cc->n2;
    uint nF = cc->n3;

    QString header =
        QString(
            "ply \nformat ascii 1.0 \nelement vertex %1\nproperty float32 bt2 "
            "\nproperty float32 radius \nproperty float32 x \nproperty float32 "
            "y \nproperty float32 z \nelement edge %2\nproperty int32 vertex1 "
            "\nproperty int32 vertex2 \nelement face %3\nproperty list uint8 "
            "int32 vertex_indices \nend_header \n")
            .arg(nV)
            .arg(nE)
            .arg(nF);
    out << header;

    for (uint i = 0; i < nV; i++) {
      out << cc->c1[i][0] << " " << cc->c1[i][1] << " " << cc->c1[i][2] << " "
          << cc->c1[i][3] << " " << cc->c1[i][4] << endl;
    }

    for (uint i = 0; i < nE; i++) {
      out << cc->c2[i][0] << " " << cc->c2[i][1] << " " << endl;
    }

    for (uint i = 0; i < nF; i++) {
      out << "3 " << cc->c3[i][0] << " " << cc->c3[i][1] << " " << cc->c3[i][2]
          << " " << endl;
    }
    return 0;
  } else {
    return 1;
  }
}

void** CCData::flatten(void) {
  void** ans = new void*[3];

  float* ans1 = new float[(this->n1) * 3];
  for (uint i = 0; i < this->n1; i++) {
    ans1[3 * i + 0] = this->c1[i][2];
    ans1[3 * i + 1] = this->c1[i][3];
    ans1[3 * i + 2] = this->c1[i][4];
  }

  int* ans2 = new int[(this->n2) * 2];
  for (uint i = 0; i < this->n2; i++) {
    ans2[2 * i + 0] = this->c2[i][0];
    ans2[2 * i + 1] = this->c2[i][1];
  }

  int* ans3 = new int[(this->n3) * 3];
  for (uint i = 0; i < this->n3; i++) {
    ans3[3 * i + 0] = this->c3[i][0];
    ans3[3 * i + 1] = this->c3[i][1];
    ans3[3 * i + 2] = this->c3[i][2];
  }
  ans[0] = ans1;
  ans[1] = ans2;
  ans[2] = ans3;
  return ans;
}
