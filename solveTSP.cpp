//
//  solveTSP.cpp
//  TravellingSalesmanProblem
//
//  Created by Ирина Женевская on 18.06.17.
//  Copyright © 2017 Женевская Ирина. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "solveTSP.h"

using namespace std;

solveTSP::solveTSP()
{
}

template<class ForwardIt>
ForwardIt max_element_my(ForwardIt first, ForwardIt last)
{
    if (first == last) {
        return last;
    }
    ForwardIt largest = first;
    ++first;
    for (; first != last; ++first) {
        if (*largest < *first) {
            largest = first;
        }
    }
    return largest;
}

void solveTSP::mInputData(){
    // Поскольку файл с данными находится вне директории, в которую X-Code компиллирует проекты, указан абсолютный путь к файлу с исходными данными
    fstream in;
    in.open("/Volumes/HDD/Irina/МАИ/КП/TravellingSalesmanProblem/TravellingSalesmanProblem/inputData.txt", ios::in);
    
    if(!in){
        cout << "Error opening file! \n";
        exit(1);
    }
    
    in >> n;
    
    mtxA.resize(n + 1);
    
    for (int i=0, size=(int)mtxA.size(); i<size; ++i) mtxA[i].resize(n+1);
    
    for(int i = 1; i <= n;i++)
    {
        for(int j = 1;j <= n;j++){
            in >>mtxA[i][j];
            if(i == j) mtxA[i][j] = M;
        }
    }
    
    for(int i = 1; i <= n;i++)
    {
        mtxA[0][i] = i;
        mtxA[i][0] = i;
    }
}

void solveTSP::mShowData(){
    cout << "\n A = ";
    for (int i = 0; i <= n; i++){
        cout << "\n";
        for (int j = 0; j <= n; j++)
            cout << " " << fixed << setprecision(3) << setw(10)<< mtxA[i][j];
    }
    cout << "\n";
}

void solveTSP::mShowWay(int size){
    cout << "\n way: ";
    for (int i = 0; i < size; i++){
        cout << vecWay[i].first << " - " << vecWay[i].second << "; ";
    }
    cout << "\n";
}

double solveTSP::mFindMinElemRow(vector<vector<double>> mtx, int index){
    return *min_element(mtx[index].begin()+1, mtx[index].end());
}

double solveTSP::mFindMinElemColomn(vector<vector<double>> mtx, int index){
    double minElem = mtx[1][index];
    for(int j = 1; j <= n; j++){
        if(mtx[j][index] < minElem){
            minElem = mtx[j][index];
        }
    }
    return minElem;
}

double solveTSP::mFindMinElemRowExpulsion(vector<vector<double>> mtx, int index, int indexEx){
    double minElem = M;
    for(int j = 1; j <= n; j++){
        if(j != indexEx && mtx[index][j] < minElem){
            minElem = mtx[index][j];
        }
    }
    return minElem;
}

double solveTSP::mFindMinElemColomnExpulsion(vector<vector<double>> mtx, int index, int indexEx){
    double minElem = M;
    for(int j = 1; j <= n; j++){
        if(j != indexEx && mtx[j][index] < minElem){
            minElem = mtx[j][index];
        }
    }
    return minElem;
}

double solveTSP::mSumEval(){
    double sum = 0;
    for_each(vecRk.begin(), vecRk.end(), [&] (int n) {
        sum += n;
    });
    for_each(vecHk.begin(), vecHk.end(), [&] (int n) {
        sum += n;
    });
    return sum;
}

vector<pair<int, int>> solveTSP::mFindIndexZeroElem(vector<vector<double>> mtx){
    vector<pair<int, int>> vecRes;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(!mtx[i][j]) vecRes.push_back(pair<int, int>(i,j));
        }
    }
    return vecRes;
}

vector<vector<double>> solveTSP::mEraseRow(vector<vector<double>> mtx, int index){
    mtx.erase(mtx.begin() + index, mtx.begin() + index + 1);
    return mtx;
}

vector<vector<double>> solveTSP::mEraseColomn(vector<vector<double>> mtx, int index){
    for(int i = 0; i <= n -1; i++){
        mtx[i].erase(mtx[i].begin() + index);
    }
    return mtx;
}

pair<int, int> solveTSP::GetRealIndex(pair<int, int> im){
    pair<int, int> r(100, 100);
    
    for (int i = 1; i <= n; i++)
    {
        if (mtxA[i][0] == im.first)
            r.first = i;
        
        if (mtxA[0][i] == im.second)
            r.second = i;
    }
    
    return r;
}

void solveTSP::mSelectSet(int index){
    pair<int, int> rIdx = GetRealIndex(vecWay.back());
    
    mtxA = mEraseRow(mtxA, rIdx.first);
    mtxA = mEraseColomn(mtxA, rIdx.second);
    
    n --;
    
    if (mtxA.size() == 2)
        return;
    
    if(vecWay.size() == 1 ){
        rIdx = GetRealIndex(make_pair(vecWay.back().second, vecWay.back().first)); // reversed from way vector
        
        mtxA[rIdx.first][rIdx.second] = M;
    }
    else{
        if(vecWay[index - 1].second == vecWay[index - 2].first){
            rIdx = GetRealIndex(make_pair(vecWay[index-2].second, vecWay[index-1].first));
            
            mtxA[rIdx.first][rIdx.second] = M;
        }
        else{
            rIdx = GetRealIndex(make_pair(vecWay.back().second, vecWay.back().first)); // reversed from way vector
            
            mtxA[rIdx.first][rIdx.second] = M;
        }
    }
    
    vecRk.clear();
    vecHk.clear();
    
    mtxA = mChangeMtx(mtxA);
    
    vecRk.clear();
    vecHk.clear();
}

vector<vector<double>> solveTSP::mChangeMtx(vector<vector<double>> mtx){
    for(int i = 1; i <= n; i++){
        vecRk.push_back(mFindMinElemRow(mtx, i));
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            mtx[i][j] -= vecRk[i-1];
        }
    }
    for(int i = 1; i <= n; i++){
        vecHk.push_back(mFindMinElemColomn(mtx, i));
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            mtx[j][i] -= vecHk[i-1];
        }
    }
    return mtx;
}

void solveTSP::mFindEval(){
    vector<double> vecEval;
    vector<pair<int, int>> vecIndex;
    
    vecIndex = mFindIndexZeroElem(mtxA);
    
    for(int i = 1; i < vecIndex.size(); i++){
        vecEval.push_back(mFindMinElemColomnExpulsion(mtxA, vecIndex[i-1].second, vecIndex[i-1].first)
                          + mFindMinElemRowExpulsion(mtxA, vecIndex[i-1].first, vecIndex[i-1].second));
    }
    
    vector<double>::iterator it = max_element_my(vecEval.begin(), vecEval.end());
    
    int m = mtxA[vecIndex[distance(vecEval.begin(), it)].first][0];
    int n = mtxA[0][vecIndex[distance(vecEval.begin(), it)].second];
    
    vecWay.push_back(make_pair(m, n));
}

void solveTSP::mSolve(){
    mShowData();
    mtxA = mChangeMtx(mtxA);
    mFindEval();
    d0 = mSumEval();
    int size = n;
    for(int i = 1; i < size; i++){
        mSelectSet(i);
        mShowData();
        mFindEval();
    }
    mShowWay(size);
}

