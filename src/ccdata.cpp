#include "ccdata.h"

//CCData::CCData(){
//    n1 = 0;
//    n2 = 0;
//    n3 = 0;

//    c1 = nullptr;
//    c2 = nullptr;
//    c2 = nullptr;
//}

CCData::~CCData(){
    delete[] c1;
    delete[] c2;
    delete[] c3;
}

CCData* CCData::LoadPLYFile(QString path){
    int numV, numE, numF;

    int nfV = 5;
    int nfE = 2;
    int nfF = 4;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;

    QTextStream in(&file);

    int headerLength = 14;
    QString header[14];
    for(int i = 0;i < headerLength; i++){
        header[i] = in.readLine();
    }

    // extract number of vertex
    numV = header[2].split(" ").at(2).toInt();

    // extract number of edge
    numE = header[8].split(" ").at(2).toInt();

    // extract number of face
    numF = header[11].split(" ").at(2).toInt();

    float** v = new float*[numV];
    int** e = new int*[numE];
    int** f = new int*[numF];

    //v
    for(int i = 0;i < numV;i++){
        QStringList vL = in.readLine().split(" ");
        v[i] = new float[nfV];
        for(int j = 0;j < nfV;j++){
            v[i][j] = vL.at(j).toFloat();
        }
    }
    //e
    for(int i = 0;i < numE;i++){
        QStringList eL = in.readLine().split(" ");
        e[i] = new int[nfE];
        for(int j = 0;j < nfE;j++){
            e[i][j] = eL.at(j).toInt();
        }
    }

    //f
    for(int i = 0;i < numF;i++){
        QStringList fL = in.readLine().split(" ");
        f[i] = new int[nfF-1];
        for(int j = 1;j < nfF;j++){ // effective data start from second field
            f[i][j-1] = fL.at(j).toInt();
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

int CCData::SaveCCData(QString path, CCData* data){
    return 0;
}




















