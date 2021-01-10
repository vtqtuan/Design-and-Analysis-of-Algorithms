/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for the interpolation search with decrease
 * and conquer approach
 * **/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct SearchProblem {
    unsigned int n;
    vector<float> lst;
    float x;
};
void readTestFile (const char* path, SearchProblem& p);
int InterpolationSearch (const vector<float>& arr, int left, int right, float key);
int main() {
    SearchProblem p;
    readTestFile("input_4.txt", p);
    int i = InterpolationSearch(p.lst, 0, p.n-1, p.x);
    cout << i;
    return 0;
}
void readTestFile (const char* path, SearchProblem& p) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        fin >> p.n;
        for (int i=0; i<p.n; i+=1) {
            float inp;
            fin >> inp;
            p.lst.push_back(inp);
        }
        fin >> p.x;
        fin.close();
    }
    return;
}
int InterpolationSearch (const vector<float>& arr, int left, int right, float key) {
    int x = left + int((key-arr[left])*(right-left)/(arr[right]-arr[left]));
    if (arr[x] == key) {
        return x;
    }
    if (arr[x] > key) {
        InterpolationSearch(arr, left, x-1, key);
    }
    else {
        InterpolationSearch(arr, x+1, right, key);
    }
}