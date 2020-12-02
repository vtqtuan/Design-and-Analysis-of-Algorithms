/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for the n-Queens problem with backtracking
 * approach
*/
#include <iostream>
#include <string>
#include <memory.h>
#include <fstream>
#include <vector>
using namespace std;
void readTestFile (const string& path, int*& col, int& n);
bool promising(int i);
void solveNQueens(int i, int* &col, const int& n, vector<int*>& lst_sols);
void printSolution(const vector<int*>& lst_sols, const int& n);
int main() {
    int* nQueens = nullptr;
    int n = 0;
    vector<int*> lst_sols;
    readTestFile("input_1.txt", nQueens, n);
    solveNQueens(-1, nQueens, n, lst_sols);
    printSolution(lst_sols, n);
    return 0;
}
void readTestFile (const string& path, int*& col, int& n) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        fin >> n;
        col = new int[n];
        fin.close();
    }
    return;
}
// Check the queen above row i is valid
bool promising(int i, const int* col) {
    int j = 0;
    bool flag = true;
    while (j < i && flag) {
        if (col[i] == col[j] || abs(col[i] - col[j]) == abs(i-j))
            flag = false;
        j++;
    }
    return flag;
}
void solveNQueens(int i, int* &col, const int& n, vector<int*>& lst_sols) {
    if (promising(i, col)) {
        if (i == n-1) {
            int* res = new int[n];
            memcpy(res, col, sizeof(int)*n);
            lst_sols.push_back(res);
        }
        else {
            for (size_t j = 0; j < n; j++)
            {
                col[i+1] = j;
                solveNQueens(i+1, col, n, lst_sols);
            }
        }
    }
}
void printSolution(const vector<int*>& lst_sols, const int& n) {
    cout << lst_sols.size() << endl;
    for (size_t i = 0; i < lst_sols.size(); i++)
    {
        for (size_t j = 0; j < n-1; j++)
        {
            cout << "(" << j << ", "<< lst_sols[i][j] <<"), ";
        }
        cout << "(" << n-1 << ", "<< lst_sols[i][n-1] <<")" << endl;
    }
}