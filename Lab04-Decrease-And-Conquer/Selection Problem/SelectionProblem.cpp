/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for the selection problem with Decrease
 * and Conquer approach
 * **/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct SelectionProblem {
    unsigned int n;
    vector<float> lst;
    int k;
    friend ostream& operator<< (ostream& os, const SelectionProblem& p) {
        os << p.n << endl;
        for (int i=0; i<p.n; i+=1) {
            os << p.lst[i] <<" ";
        }
        os << endl << p.k;
        return os;
    }
};
void readTestFile (const char* path, SelectionProblem& p);
int Partition (vector<float>& arr, int lower, int upper, int pos);
float Selection (vector<float>& arr, int lower, int upper, int k);
int main() {
    SelectionProblem prb;
    readTestFile("input_3.txt", prb);
    cout << Selection(prb.lst, 0, prb.n-1, prb.k);
    return 0;
}
void readTestFile (const char* path, SelectionProblem& p) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        fin >> p.n;
        for (int i=0; i<p.n; i+=1) {
            float inp;
            fin >> inp;
            p.lst.push_back(inp);
        }
        fin >> p.k;
        fin.close();
    }
    return;
}
int Partition (vector<float>& arr, int lower, int upper, int pos) {
    float pivot = arr[pos];
    swap(arr[lower], arr[upper]);
    pos = lower;
    for (int i = lower+1; i<=upper; i++) {
        if (pivot > arr[i]) {
            pos++;
            swap(arr[i], arr[pos]);
        }
    }
    swap(arr[lower], arr[pos]);
    return pos;
}
float Selection (vector<float>& arr, int lower, int upper, int k) {
    int h = (rand()%upper)+lower;
    int pos = Partition(arr, lower, upper, h);
    if (pos == k-1) {
        return arr[pos];
    }
    if (pos > k-1) {
        Selection(arr, lower, pos-1, k);
    }
    if (pos < k-1) {
        Selection(arr, pos+1, upper, k);
    }
}