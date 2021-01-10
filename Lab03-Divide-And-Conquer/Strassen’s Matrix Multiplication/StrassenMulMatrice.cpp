/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for Strassen's Multiplication two matrices 
 * problem with divide and conquer approach **/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
typedef vector<int> arr1d;
typedef vector<arr1d> arr2d;
//typedef vector<arr2d> partitions; // list of four sub matrices
struct MulMatrices {
    int n;
    arr2d a, b; // two matrices in multiplication operation.
    arr2d res;
    friend ostream& operator<< (ostream& os, const MulMatrices& p) {
        os << p.n << endl;
        if (p.n != 0) {
            for (int i=0; i<p.n; i+=1) {
                for (int j=0; j<p.n; j+=1) {
                    cout << p.a[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            for (int i=0; i<p.n; i+=1) {
                for (int j=0; j<p.n; j+=1) {
                    cout << p.b[i][j] << " ";
                }
                cout << endl;
            }
        }
        return os;
    }
    void printResult() {
        for(int i=0; i<res.size(); i+=1) {
            for (int j=0; j<res.size(); j+=1) {
                cout << res[i][j] << " ";
            }
            cout << endl;
        }
    }
    void getTestFile (const string& path) {
        fstream fin;
        fin.open(path, ios::in);
        if (fin.is_open()) {
            fin >> n;
            int inp;
            for (int i=0; i<n; i+=1) {
                arr1d arr_inp;
                for (int j=0; j<n; j+=1) {
                    fin >> inp;
                    arr_inp.push_back(inp);
                }
                a.push_back(arr_inp);
            }
            for (int i=0; i<n; i+=1) {
                arr1d arr_inp;
                for (int j=0; j<n; j+=1) {
                    fin >> inp;
                    arr_inp.push_back(inp);
                }
                b.push_back(arr_inp);
            }
            arr2d tmp(n, arr1d(n, 0));
            res = tmp;
            fin.close();
        }
        return;
    }
};
arr2d sumMatrices (const arr2d& a, const arr2d& b);
arr2d subtractMatrices (const arr2d& a, const arr2d& b);
arr2d slicing(const arr2d& a, const int& endRow, const int& endCol,
                const int& beginRow, const int& beginCol);
void printMatrix(const arr2d& a) {
    for (int i=0; i<a.size(); i+=1) {
        for (int j=0; j<a[i].size(); j+=1) {
            cout << a[i][j] <<" ";
        }
        cout << endl;
    }
}
void reslicing (arr2d& dest, const arr2d& src, 
                const int& endRow, const int& endCol,
                const int& beginRow, const int& beginCol);
void partition (const arr2d& src, arr2d& a11, arr2d &a12, arr2d& a21, arr2d& a22);
arr2d combine (const arr2d& a11, const arr2d& a12,
                 const arr2d& a21, const arr2d& a22);
void padding (arr2d& a);
void Strassen (int n, arr2d a, arr2d b, arr2d& c);
int main() {
    MulMatrices prob;
    prob.getTestFile("input_2.txt");
    Strassen(prob.n, prob.a, prob.b, prob.res);
    prob.printResult();
    return 0;
}
arr2d sumMatrices (const arr2d& a, const arr2d& b) {
    arr2d res(a.size(), arr1d(a.size(), 0));
    for (int i=0; i<a.size(); i+=1) {
        for (int j=0; j<a.size(); j+=1) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
    return res;
}
arr2d subtractMatrices (const arr2d& a, const arr2d& b) {
    arr2d res(a.size(), arr1d(a.size(), 0));
    for (int i=0; i<a.size(); i+=1) {
        for (int j=0; j<a.size(); j+=1) {
            res[i][j] = a[i][j] - b[i][j];
        }
    }
    return res;
}
arr2d slicing(const arr2d& a, const int& endRow, const int& endCol,
                const int& beginRow, const int& beginCol) {
    /**
     * Using for slicing an matrix, with endRow an endCol is the index of a
     * length for initialize the result matrix is endRow+1, endCol+1
     * it will be liked: res[endRow-beginRow+1][endCol-beginCol+1]
     */
    arr2d res(endRow-beginRow+1, arr1d(endCol-beginCol+1, 0));
    for (int i=0; i<endRow-beginRow+1; i+=1) {
        for (int j=0; j<endCol-beginCol+1; j+=1) {
            res[i][j] = a[i+beginRow][j+beginCol];
        }
    }
    return res;
}
void reslicing (arr2d& dest, const arr2d& src, 
                const int& endRow, const int& endCol,
                const int& beginRow, const int& beginCol) {
    for (int i=0; i<endRow-beginRow+1; i+=1) {
        for (int j=0; j<endCol-beginCol+1; j+=1) {
            dest[i+beginRow][j+beginCol]=src[i][j];
        }
    }
}
arr2d combine (const arr2d& a11, const arr2d& a12,
                 const arr2d& a21, const arr2d& a22) {
    int n = a11.size()*2;
    arr2d res(n, arr1d(n, 0));
    reslicing(res, a11, a11.size()-1, a11.size()-1, 0, 0);
    reslicing(res, a12, a12.size()-1, a12.size()*2-1, 0, a11.size());
    reslicing(res, a21, a11.size()*2-1, a11.size()-1, a11.size(), 0);
    reslicing(res, a22, a22.size()*2-1, a22.size()*2-1, a12.size(), a21.size());
    return res;
}
void padding (arr2d& a) {
    arr2d res(a.size()+1, arr1d(a.size()+1, 0));
    reslicing(res, a, res.size()-2, res.size()-2, 0, 0);
    a = res;
}
void partition (const arr2d& src, arr2d& a11, arr2d &a12, arr2d& a21, arr2d& a22) {
    int n = src.size()/2;
    a11 = slicing(src, n-1, n-1, 0, 0);
    a12 = slicing(src, n-1, 2*n-1, 0, n);
    a21 = slicing(src, 2*n-1, n-1, n, 0);
    a22 = slicing(src, 2*n-1, 2*n-1, n, n);
}
void Strassen (int n, arr2d a, arr2d b, arr2d& c) {
    if (n <= 1) {
        arr2d tmp(1, arr1d(1, 0));
        c = tmp;
        c[0][0] = a[0][0]*b[0][0];
    }
    else {
        if (n%2 != 0) {
            padding(a);
            padding(b);
            n+=1;
        }
        arr2d a11, a12, a21, a22;
        arr2d b11, b12, b21, b22;
        partition(a, a11, a12, a21, a22);
        partition(b, b11, b12, b21, b22);

        arr2d m1, m2, m3, m4, m5, m6, m7;
        Strassen(n/2, sumMatrices(a11, a22), sumMatrices(b11, b22), m1);
        Strassen(n/2, sumMatrices(a21, a22), b11, m2);
        Strassen(n/2, a11, subtractMatrices(b12, b22), m3);
        Strassen(n/2, a22, subtractMatrices(b21, b11), m4);
        Strassen(n/2, sumMatrices(a11, a12), b22, m5);
        Strassen(n/2, subtractMatrices(a21, a11), sumMatrices(b11, b12), m6);
        Strassen(n/2, subtractMatrices(a12, a22), sumMatrices(b21, b22), m7);

        arr2d c11, c12, c21, c22;
        c11 = sumMatrices(subtractMatrices(sumMatrices(m1, m4),m5), m7);
        c12 = sumMatrices(m3, m5);
        c21 = sumMatrices(m2, m4);
        c22 = sumMatrices(subtractMatrices(sumMatrices(m1, m3),m2), m6);
        
        c = combine(c11, c12, c21, c22);
    }
}