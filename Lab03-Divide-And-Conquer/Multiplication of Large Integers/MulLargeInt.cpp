/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for multiplication two large integers numbers
 * in divide-and-conquer approach.
 * **/
#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
struct MulLargeInt
{
    long long a;
    long long b;
    long long res;
    friend ostream& operator<< (ostream& os, const MulLargeInt& p) {
        os << p.res;
        return os;
    }
};

void readTestFile (const char* path, MulLargeInt& p);
long long largeIntegerMul (long long a,long long b);
void solveTheLargeIntMul (MulLargeInt& p);
int main() { 
    MulLargeInt prob;
    readTestFile ("input_1.txt", prob);
    solveTheLargeIntMul(prob);
    cout << prob;
    return 0;
}
void readTestFile (const char* path, MulLargeInt& p) {
    fstream fin;
    fin.open(path, ios::in);
    if (fin.is_open()) {
        fin >> p.a;
        fin >> p.b;
        p.res = 0;
        fin.close();
    }
    return;
}
long long largeIntegerMul (long long a,long long b) {
    long long x, y, w, z;
    int n = max(to_string(a).size(), to_string(b).size());
    if (a==0 || b==0) {
        return 0;
    }
    else {
        if (n <= 1) {
            return a*b;
        }
        else {
            int m = int(n/2);
            x = div(a, (long long)pow(10, m)).quot;
            y = a % (long long)pow(10, m);
            w = div(b, (long long)pow(10, m)).quot;
            z = b % (long long)pow(10, m);
            return largeIntegerMul(x, w)*pow(10, 2*m) + (largeIntegerMul(x, z) + largeIntegerMul(y, w))*pow(10, m) + largeIntegerMul(y, z);
        }
    }
}
void solveTheLargeIntMul (MulLargeInt& p) {
    p.res = largeIntegerMul(p.a, p.b);
}