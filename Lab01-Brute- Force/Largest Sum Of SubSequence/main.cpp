/*************************************************************************
*   This code was implemented for finding the sub sequence with largest  *
*   sum of element in an given real array                                *
*   Author: Quang-Tuan Vo-Tran                                           *
**************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
/*  All function using for testing and implementing the algorithm for     
    finding the sub sequence with largest sum of element in an given real
    array  
*/

//  Reading the testing file input                                                                                                  
void readTestFile(float* &a, int& n, const string& path);
//  Writing the result file output after involve the algorithm                                                                                       
void writeResFile(const string& path, const float* a, const int& n);

/*  Tracing the sub sequence from the original array with start position 
    and length of this sub sequence
*/
float* tracing(const float* originalArray, const int& n, const int& start, const int& length);
//  Finding the subsequence with max sum
float* findSubSeqMaxSum(const float* a, const int& n);

void printSolution(const float* a, const int& n);
int main() {
    vector<string> listTestFile = {"input_2.txt"};

    float* testArray = nullptr;
    float* resArray = nullptr;
    int n = 0;
    int lengthOfRes = 0;
    readTestFile(testArray, n, listTestFile[0]);
    resArray = findSubSeqMaxSum(testArray, n);
    lengthOfRes = int(resArray[0]);
    printSolution(resArray, lengthOfRes);
    return 0;
}

void readTestFile(float* &a, int& n, const string& path) {
    /*  Implementing procedure reading testing file input   */
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
    /*  Implementing procedure writing result file output   */
    if (a == nullptr) {
        cout << "illegal array!" << endl;
        cout << 0;
        return;
    }
    for (size_t i = 2; i < n+2; i++)
    {
        /* code */
        cout << a[i] << " ";
    }
    cout << endl;
    cout << a[1];
}

float* tracing(const float* originalArray, const int& n, const int& start, const int& length) {
    float* res = new float[length+2];
    res[0] = length;
    for (size_t i = 2; i < length+2; i++)
    {
        /* code */
        res[i] = originalArray[start + i - 2];
    }
    return res;
}

float* findSubSeqMaxSum(const float* a, const int& n) {
    float maxSum = 0;
    float tempSum = 0;

    int startTrace = 0;
    int length = 0;
    int tmpLength = 0;
    for (size_t i = 0; i < n; i++)
    {
        /* code */
        tmpLength += 1;
        tempSum += a[i];
        if (maxSum < tempSum) {
            maxSum = tempSum;
            length = tmpLength;
        }
        if (tempSum <= 0) {
            tempSum = 0;
            startTrace = i + 1;
            tmpLength = 0;
        }
    }
    if (length == 0) {
        return nullptr;
    }
    float* res = tracing(a, n, startTrace, length);
    res[1] = maxSum;
    return res;
}