#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Read the test file
void readTestFile(const string& path, int* &a, int &n) {
    fstream fin;
    fin.open(path, ios::in);
    if (!fin.is_open()) 
    {
        cout << "Can't read test file!\n";
        return;
    }
    fin >> n;
    a = new int[n];
    for (size_t i = 0; i < n; i++)
    {
        fin >> a[i];
    }
}

// write the result file
void writeResultFile(const string& path, const int* a) {
    if (a == nullptr) return;
    fstream fout;
    fout.open(path, ios::out);
    fout << a[0] << endl; // the length of array
    fout << a[a[0] + 1] << endl; // the sum of array
    for (size_t i = 1; i < a[0] + 1; i++)
    {
        fout << a[i] << " ";
    }
}
// tracing the subsequence.
int* tracing(const int* a, const int& resLength, const int& traceIndex) {
    if (resLength == 0) return nullptr;
    int* resArray = new int[resLength + 2];
    // the first element of resArray is length of array
    resArray[0] = resLength;
    // tracing the subsequence from the testArray
    for (size_t i = traceIndex; i < traceIndex + resLength; i++)
    {
        // subsequence traced from a and trace index
        resArray[i-traceIndex+1] = a[i];
    }
    return resArray;
}

// find the max sum and subsequence.
int* findMaxSum(const int* a, const int& n) {
    int maxSum = 0;
    // temporatory sum
    int tmpSum = 0;
    // temporary trace index
    int tmpTraceIndex = 0;
    // trace index;
    int traceIndex = 0;
    // temporary length of array
    int tmpResLength = 0;
    // length of subsequence
    int resLength = 0;
    for (size_t i = 0; i < n; i++)
    {
        // array's length
        int tmpResLength = 0;
        tmpTraceIndex = i;
        tmpSum = 0;
        for (size_t j = i; j < n; j++)
        {
            tmpSum += a[j];
            tmpResLength += 1;
            if (tmpSum > maxSum) {
                // update max sum
                maxSum = tmpSum;
                //update length of subsequence
                resLength = tmpResLength;
                //update trace index
                traceIndex = tmpTraceIndex;
            }
        }
    }
    
    int* resArray = nullptr;
    resArray = tracing(a, resLength, traceIndex);
    if (resArray != nullptr) {
        resArray[resLength + 1] = maxSum;
    }
    return resArray;
}

int main() {
    vector<string> listOfTest= {"test01.txt", "test02.txt", "test03.txt"};
    vector<string> listOfRes = {"result01.txt", "result02.txt", "result02.txt"};
    int* testArray = nullptr;
    int n = 0;
    for (size_t i = 0; i < listOfTest.size(); i++)
    {
        readTestFile(listOfTest[i], testArray, n);
        int* resArray = findMaxSum(testArray, n);
        writeResultFile(listOfRes[i], resArray);
    }
    return 0;
}