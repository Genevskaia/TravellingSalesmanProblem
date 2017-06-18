//
//  solveTSP.h
//  TravellingSalesmanProblem
//
//  Created by Ирина Женевская on 18.06.17.
//  Copyright © 2017 Женевская Ирина. All rights reserved.
//

#ifndef solveTSP_h
#define solveTSP_h

#include <vector>

using namespace std;

class solveTSP
{
public:
    solveTSP();
    void mInputData();
    void mShowData();
    double mFindMinElemRow(vector<vector<double>> mtx, int index);
    double mFindMinElemColomn(vector<vector<double>> mtx, int index);
    double mFindMinElemRowExpulsion(vector<vector<double>> mtx, int index, int indexEx);
    double mFindMinElemColomnExpulsion(vector<vector<double>> mtx, int index, int indexEx);
    double mSumEval();
    vector<pair<int, int>> mFindIndexZeroElem(vector<vector<double>> mtx);
    vector<vector<double>> mEraseRow(vector<vector<double>> mtx, int index);
    vector<vector<double>> mEraseColomn(vector<vector<double>> mtx, int index);
    void mSelectSet(int index);
    vector<vector<double>> mChangeMtx(vector<vector<double>> mtx);
    void mFindEval();
    void mSolve();
    void mShowWay(int size);
    pair<int, int> GetRealIndex(pair<int, int> im);
private:
    vector<vector<double>> mtxA;
    vector<pair<int, int>> vecWay;
    vector<double> vecHk;
    vector<double> vecRk;
    
    double d0;
    int n;
    int M = 10000;
    int c = 0;
};


#endif /* solveTSP_h */
