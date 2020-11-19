/****************************************************************
*   This source code was implemented for shaker sort algorithm. *
*   Author: Quang-Tuan Vo-Tran                                  *
*****************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
/*  All function using for testing and implementing shaker sort */

//  Reading the testing file input for shaker sort
void readTestFile(float* &a, int& n, const string& path);
void printSolution(const float* a, const int& n);
//  Implementing Shaker Sort
void swap(float& x, float& y);
void shakerSort(float* a, const int& n);
int main() {
    vector<string> listTestFile = {"input_1.txt"};

    float* testArray = nullptr;
    int n = 0;
    readTestFile(testArray, n, listTestFile[0]);
    shakerSort(testArray, n);
    printSolution(testArray, n);
    
    return 0;
}

void readTestFile(float* &a, int& n, const string& path) {
    /*  Implementing procedure reading testing file input for   
    *   shaker sort                                             
    */
    fstream fin;
    fin.open(path, ios::in);
    if (!fin.is_open()) {
        cout << "Can't read the test file " << path << endl; 
        return;
    }
    fin >> n;
    a = new float[n];
    for (size_t i = 0; i < n; i++)
    {
        /* code */
        fin >> a[i];
    }
}

void printSolution(const float* a, const int& n) {
    /*  Implementing procedure writing result file output after 
    *   involve Shaker Sort                                     
    */
    if (a == nullptr) {
        cout << "illegal array!" << endl;
        return;
    }
    for (size_t i = 0; i < n; i++)
    {
        /* code */
        cout << a[i] << " ";
    }
}

void swap(float& x, float& y)
{
    float temp = x;
    x = y;
    y = temp;
}
void shakerSort(float* a, const int& n)
{
    /*  Implementing Shaker Sort Algorithm
    */
    int length = n;
    bool swapped = false;
    int begin = 0;
    int end = length-2;

    do {
        swapped = false;
        for (size_t i = begin; i <= end; i++)
        {
            if (a[i] > a[i+1]) {
                swap(a[i], a[i+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        for (int j = end; j >= begin; j--)
        {
            if (a[j] > a[j+1]) {
                swap(a[j], a[j+1]);
                swapped = true;
            }
        }
        begin++;
        end--;

    } while (swapped);
}