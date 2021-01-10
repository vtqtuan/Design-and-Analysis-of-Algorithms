/**
 * @file KnapSach.cpp
 * @author Quang-Tuan Vo-Tran (18127248@student.hcmus.edu.vn)
 * @brief This code was implemented for the Knapsach problem with dynamic programming
 * technique.
 * @version 0.1
 * @date 2021-01-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
struct KnapSach
{
    int W_max;
    vector<int> w;
    vector<int> v;
    friend ostream& operator<< (ostream& os, const KnapSach& p) {
        os << p.W_max << endl;
        for (int i=0; i<p.v.size(); i++) {
            os << p.w[i] <<" "<<p.v[i] << endl;
        }
        return os;
    }
};
bool readTestFile (const char* path, KnapSach& p) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        fin >> p.W_max;
        int n;
        fin >> n;
        p.w = vector<int>(n, 0);
        p.v = vector<int>(n, 0);
        for (int i=0; i<n; i++) {
            fin >> p.w[i] >> p.v[i];
        }
        fin.close();
        return true;
    }
    return false;
}
void printSolution (const vector<vector<int>>& T, const KnapSach& p,
                    int i, int j, vector<int>& sol) {
    if ( i == 0 || j== 0) {
        return;
    }
    if (T[i][j] == T[i-1][j]) {
        printSolution (T, p, i-1, j, sol);
    }
    else {
        sol.push_back(i-1);
        printSolution(T, p, i-1, j-p.w[i-1], sol);
    }
}
int solveKnapSach (const KnapSach& p) {
    int n = p.w.size(); // number of items
    int C = p.W_max; // capacity
    vector<vector<int>> T(n+1, vector<int>(C+1, 0));
    for (int i=1; i <= n; i++) {
        for (int j=1; j<= C; j++) {
            if (j >= p.w[i-1]) {
                T[i][j] = max(T[i-1][j], p.v[i-1] + T[i-1][j-p.w[i-1]]);
            }
            else {
                T[i][j] = T[i-1][j];
            }
        }
    }
    vector<int> sol;
    printSolution(T, p, n, C, sol);
    reverse(sol.begin(), sol.end());
    for (int i=0; i<sol.size(); i++) {
        cout << sol[i] <<" ";
    }
    cout << endl << T[n][C];
    return T[n][C];
}
int main() {
    KnapSach p;
    readTestFile ("input_7.txt", p);
    solveKnapSach(p);
    return 0;
}