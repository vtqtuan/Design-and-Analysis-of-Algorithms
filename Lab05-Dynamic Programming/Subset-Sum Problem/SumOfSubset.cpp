/**
 * @file SumOfSubset.cpp
 * @author Quang-Tuan Vo-Tran (18127248@student.hcmus.edu.vn)
 * @brief This code was implemented for Subset-Sum Problem with dynamic programming
 * technique.
 * @version 0.1
 * @date 2020-12-31
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
struct SumOfSubset
{
    vector<int> superSet;
    int req;
    friend ostream& operator<< (ostream& os, const SumOfSubset& p) {
        os << p.superSet.size() << endl;
        for (int i=0; i<p.superSet.size(); i++) {
            os << p.superSet[i] <<" ";
        }
        os << endl << p.req;
        return os;
    }
};
bool readTestFile (const char* path, SumOfSubset& p) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        int n;
        fin >> n;
        p.superSet = vector<int>(n, 0);
        for (int i=0; i<n; i++) {
            fin >> p.superSet[i];
        }
        fin >> p.req;
        fin.close();
        return true;
    }
    return false;
}
void display (const vector<int>& a) {
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] <<" ";
    }
}

void printRes (const vector<vector<int>>& V, int n, int k, const vector<int>& a) {
    for (int i = 0; i < n; i++) {
        if (V[i][k] < V[i + 1][k]){
            int pos = k;
            int idx = i + 1;
            vector<int> sol;
            while (pos) {
                if (pos - a[idx - 1] >= 0 && V[idx][pos - a[idx - 1]] > 0) {
                    //cout << a[idx - 1] << " ";
                    sol.push_back(a[idx-1]);
                    pos -= a[idx - 1];
                }
                idx--;
            }
            reverse(sol.begin(), sol.end());
            for (int i=0; i<sol.size(); i++) {
                cout << sol[i] <<" ";
            }
            cout << endl;
        }
    }

}
void solveSumOfSubsetsDP (const SumOfSubset& p) {
    int n = p.superSet.size(), k = p.req;
    vector<vector<int>> V(n+1, vector<int>(k+1, 0));
    for (int i=0; i<=n; i++) {
        V[i][0] = 1;
    }

    for (int i=1; i<= n; i++) {
        for (int j=1; j<=k; j++) {
            int tmp = 0;
            if (j >= p.superSet[i-1]) {
                tmp = V[i-1][j-p.superSet[i-1]];
            }
            V[i][j] = V[i-1][j] + tmp;
        }
    }
    printRes(V, n, k, p.superSet);
}

int main() {
    SumOfSubset p;
    readTestFile("input_6.txt", p);
    solveSumOfSubsetsDP(p);
    return 0;
}