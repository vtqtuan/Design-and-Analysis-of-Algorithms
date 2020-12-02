/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for solving the sum of subsets with
 * backtracking version 2 approach.
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
void printSolution (arr1D& res, const int& size);
void SoS (arr1D& res, const int& size, const int& sum, const int & start, const int& t, const arr1D& w);
void solveSos (const SumOfSubset& prob);
int main() {
    SumOfSubset prob;
    readTestFile("input_3.txt", prob);
    solveSos(prob);
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
void printSolution (arr1D& res, const int& size) {
    for (int i=0; i<size; i++) {
        cout << res[i] << " ";
    }
}
void SoS (arr1D& res, const int& size, const int& sum, const int & start, const int &t, const arr1D& w) {
    if (sum == t) {
        printSolution(res, size);
    }
    else {
        for (int i = start; i <= res.size(); i++) {
            res[size] = w[i];
            SoS(res, size+1, sum+w[i], i+1, t, w);
        }
    }
}
void solveSos (const SumOfSubset& prob) {
    int length = prob.lst.size();
    arr1D res(length, 0);
    int total = computeSum(prob.lst);
    if (prob.lst[0] <= prob.req && prob.req <= total) {
        SoS(res, 0, 0, 0, prob.req, prob.lst);
    }
}