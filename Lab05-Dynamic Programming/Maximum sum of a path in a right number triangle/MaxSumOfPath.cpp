/**
 * @file MaxSumOfPath.cpp
 * @author Quang-Tuan Vo-Tran (18127248@student.hcmus.edu.vn)
 * @brief This code was implemented for finding the maximum sum of a path
 * in a right number triangle with dynamic programming technique
 * @version 0.1
 * @date 2020-12-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> arr1d;
typedef vector<arr1d> arr2d;
void readTestFile (const char* path, arr2d& inp);
void findThePathWithMaxSum (const arr2d& a);
int main() {
    arr2d p;
    readTestFile ("input_1.txt", p);
    findThePathWithMaxSum(p);
    return 0;
}
void readTestFile (const char* path, arr2d& inp) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        int n; fin >> n;
        arr2d tmp(n, arr1d(n, 0));
        for (int i=0; i<n; i+=1) {
            for (int j=0; j<=i; j+=1) {
                fin >> tmp[i][j];
            }
        }
        inp = tmp;
        fin.close();
    }
}
void findThePathWithMaxSum (const arr2d& a) {
    int n=a.size();
    arr2d S(n+1, arr1d(n+1, 0));
    for (int i=1; i<=n; i+=1) {
        for (int j=1; j<=i; j+=1) {
            S[i][j] = max(S[i-1][j-1], S[i-1][j]) + a[i-1][j-1];
        }
    }
    cout << *max_element(S[n].begin(), S[n].end()) << endl;
    for (int i=1; i<=n; i++) {
        int j = max_element(S[i].begin(), S[i].end()) - S[i].begin();
        cout << a[i-1][j-1] << " "; 
    }
}