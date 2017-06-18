//
//  main.cpp
//  TravellingSalesmanProblem
//
//  Created by Женевская Ирина on 15.05.16.
//  Copyright © 2016 Женевская Ирина. All rights reserved.
//
//Решение задачи коммивояжера методом ветвей и границ
//Вход: размер матрицы расстояний и сама матрица расстояний
//Выход: вектор переходов
#include "solveTSP.h"

int main() {
    
    solveTSP s1;
    
    s1.mInputData();
    s1.mSolve();
    
    return 0;
}
