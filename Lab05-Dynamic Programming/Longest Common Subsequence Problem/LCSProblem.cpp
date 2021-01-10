/**
 * @file LCSProblem.cpp
 * @author Quang-Tuan Vo-Tran (18127248@student.hcmus.edu.vn)
 * @brief This code was implemented for Longest Commmon Subsequence (LCS) problem with
 * dynamic programming technique.
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
bool readTestFile (const string& path, string& s1, string& s2) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        fin >> s1;
        fin >> s2;
        fin.close();
        return true;
    }
    return false;
}

// trace to print the subsequence
void printSubSequence(const string& s1, const string& s2,
                    const vector<vector<int>>& L, const int& r, const int& c,
                    vector<char>& res) {
    // stop condition
    if (r==0 || c==0) {
        return;
    }
    if (s1[r-1]==s2[c-1]) {
        res.push_back(s1[r-1]);
        printSubSequence(s1, s2, L, r-1, c-1, res);
    }
    else {
        if (max(L[r-1][c], L[r][c-1]) == L[r-1][c]) {
            printSubSequence(s1, s2, L, r-1, c, res);
        }
        else {
            printSubSequence(s1, s2, L, r, c-1, res);
        }
    }
}
int findLCS (const string& s1, const string& s2) {
    int s1_length = s1.size();
    int s2_length = s2.size();

    // initialize the matrix save result
    vector<vector<int>> L(s1_length+1, vector<int>(s2_length+1, 0));
    for (int i=1; i<=s1_length; i+=1) {
        for (int j=1; j<=s2_length; j+=1) {
            if (s1[i-1] == s2[j-1]) {
                L[i][j] = 1 + L[i-1][j-1]; 
            }
            else {
                L[i][j] = max(L[i-1][j], L[i][j-1]);
            }
        } 
    }

    vector<char> result;
    printSubSequence(s1, s2, L, s1_length, s2_length, result);
    reverse(result.begin(), result.end());
    for (int i=0; i<result.size(); i+=1) {
        cout << result[i];
    }

    return L[s1_length][s2_length];
}
int main() {
    string s1, s2;
    readTestFile("input_3.txt", s1, s2);
    findLCS(s1, s2);
    return 0;
}