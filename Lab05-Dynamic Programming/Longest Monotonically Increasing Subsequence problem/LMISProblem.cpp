/**
 * @file LMISProblem.cpp
 * @author Quang-Tuan Vo-Tran (18127248@student.hcmus.edu.vn)
 * @brief This code was implemented for Longest Monotonically Increasing 
 * Subsequence (LMIS) problem with dynamic programming technique. 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
struct LMIS {
    vector<int> seq;
    vector<int> res;
    friend ostream& operator<< ( ostream& os, const LMIS& p) {
        for (int i=0; i<p.seq.size(); i+=1) {
            cout << p.seq[i] << " ";
        }
        return os;
    }
};
bool readTestFile (const char* path, LMIS& p) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        int n;
        fin >> n;
        vector<int> input(n, 0);
        p.seq = input;
        for (int i=0; i<n; i+=1) {
            fin >> p.seq[i];
        }
        fin.close();
        return true;
    }
    return false;
}
void traceTheSubSequence (const vector<int> & trace, const int& pos, 
                        const vector<int>& lst, vector<int>& res) {
    res.push_back(lst[pos]);
    if (trace[pos] == -1) {
        return;
    }
    traceTheSubSequence(trace, trace[pos], lst, res);
}
void find_LMIS (LMIS& p) {
    vector<int> L(p.seq.size(),1);
    vector<int> listFrontOf_i (p.seq.size(), -1);
    for (int i=1; i<p.seq.size(); i+=1) {
        int front_of_i = -1;
        for (int j=0; j<i; j+=1) {
            if (p.seq[j] < p.seq[i] && (L[j]+1 > L[i])) {
                L[i] = L[j] + 1;
                front_of_i = j;
            }
        }
        listFrontOf_i[i] = front_of_i;
    }

    // find the max length
    int max_idx = 0;
    for (int i=0; i<L.size(); i+=1) {
        if (L[i] > L[max_idx]) {
            max_idx = i;
        }
    }
    // trace for saving the LMIS
    traceTheSubSequence (listFrontOf_i, max_idx, p.seq, p.res);
    sort(p.res.begin(), p.res.end());
    for (int i=0; i<p.res.size(); i+=1) {
        cout << p.res[i] <<" ";
    }
    cout << endl << L[max_idx];
}
int main() {
    LMIS p;
    readTestFile ("input_4.txt", p);
    find_LMIS (p);
    return 0;
}