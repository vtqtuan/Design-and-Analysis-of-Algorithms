/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for finding the substring with largest sum
 * of elements in an array
 * **/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct Solution {
    int start=-1;
    int end=-1;
};
void readTestFile (const char* path, vector<int>& a);
void printArray (const vector<int>& a);
vector<int> trace (const vector<int>& src,
                    const int& left, const int& right);
int sumMax (const vector<int> a, const int& left, const int& right, Solution& sol);
int main () {
    vector<int> arr;
    Solution sol;
    readTestFile("input_3.txt", arr);
    int sum = sumMax(arr, 0, arr.size()-1, sol);
    vector<int> res = trace(arr, sol.start, sol.end);
    printArray(res);
    cout << endl << sol.start << " "<< sol.end << endl;
    cout << sum;
    return 0;
}
void readTestFile (const char* path, vector<int>& a) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        int n;
        fin >> n;
        for (int i=0; i<n; i+=1) {
            int inp;
            fin >> inp;
            a.push_back(inp);
        }
        fin.close();
    }
    return;
}
void printArray (const vector<int>& a) {
    int length = a.size();
    for (size_t i=0; i<length; i+=1) {
        cout << a[i] << " ";
    }
    return;
}
vector<int> trace (const vector<int>& src,
                    const int& left, const int& right) 
{
    vector<int> res;
    for (int i=left; i<=right; i++) {
        res.push_back(src[i]);
    }
    return res;
}
int sumMax (const vector<int> a, const int& left, const int& right, Solution& sol) {
    if (left == right) {
        if (max(a[left], 0) == a[left]) {
            sol.start = sol.end = left;
            return a[left];
        }
        else {
            return 0;
        }
    }
    int center = int((left+right)/2);
    int maxLS = sumMax(a, left, center, sol);
    int maxRS = sumMax(a, center+1, right, sol);

    int tmp, maxLpartS;
    tmp = maxLpartS = 0;
    int startTrace = -1;
    for (int i=center; i>=0; i-=1) {
        tmp+=a[i];
        if (tmp > maxLpartS) {
            startTrace = i;
            maxLpartS = tmp;
        }
    }
    int maxRpartS;
    tmp = maxRpartS = 0;
    int endTrace = -1;
    for(int i = center+1; i<=right; i++) {
        tmp+=a[i];
        if (tmp>maxRpartS) {
            maxRpartS=tmp;
            endTrace = i;
        }
    }
    sol.start = startTrace;
    sol.end = endTrace;
    tmp = maxLpartS + maxRpartS;
    return max(max(tmp, maxLS), max(tmp,maxRS));
}