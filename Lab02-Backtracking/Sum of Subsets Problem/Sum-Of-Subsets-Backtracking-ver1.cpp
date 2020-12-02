/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for solving the sum of subsets with
 * backtracking version 1 approach.
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
typedef vector<int> arr1D;
struct SumOfSubset
{
    int n;
    arr1D lst;
    int req;
    friend ostream& operator<< (ostream& os, const SumOfSubset& test) {
        os << test.n << endl;
        for (size_t i = 0; i < test.n; i++)
        {
            os << test.lst[i] << " ";
        }
        os << endl << test.req;
        return os;
    }
};
void readTestFile (const string& path, SumOfSubset& prob);
int computeSum (const arr1D& a);
void printSolution(const vector<bool>& b, const arr1D& res);
void SoS (int k, int sum, int total, const arr1D& a, vector<bool>& s, const int& t);
void solveSOS (const SumOfSubset& prob);
int main() {
    SumOfSubset prob;
    readTestFile("input_3.txt", prob);
    solveSOS(prob);
    return 0;
}
void readTestFile (const string& path, SumOfSubset& prob) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        fin >> prob.n;
        for (size_t i = 0; i < prob.n; i++)
        {
            int element;
            fin >> element;
            prob.lst.push_back(element);
        }
        fin >> prob.req;
        sort(prob.lst.begin(), prob.lst.begin() + prob.n);
        fin.close();
    }
    return;
}
int computeSum (const arr1D& a) {
    int total = 0;
    for (size_t i = 0; i < a.size(); i++)
    {
        total += a[i];
    }
    return total;
}
void printSolution(const vector<bool>& b, const arr1D& res) {
    int length = b.size();
    for (int i=0; i<length; i++) {
        if (b[i]) {
            cout << res[i] << " ";
        }
    }
}
void SoS (int k, int sum, int total, const arr1D& a, vector<bool>& s, const int& t) {
    if (sum == t) {
        printSolution(s, a);
    }
    else {
        if ((sum + total >= t) && (sum + a[k] <= t)) {
            s[k] = true;
            SoS(k+1, sum + a[k], total - a[k], a, s, t);
            s[k] = false;
            SoS(k+1, sum, total-a[k], a, s, t);
        }
    }
}
void solveSOS (const SumOfSubset& prob) {
    int length = prob.lst.size();
    vector<bool> b(length, false);
    int total = computeSum(prob.lst);
    if (prob.lst[1] <= prob.req <= total) {
        SoS(0, 0, total, prob.lst, b, prob.req);
    }
}