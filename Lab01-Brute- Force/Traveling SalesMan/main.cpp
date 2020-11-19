/**
 * Author: Quang-Tuan Vo-Tran
 * This is source C++ code implementing for Traveling Salesman Problem
 * with Brute-Force approach
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#define MAX_PATH 5000
using namespace std;
typedef int* arr1D;
typedef arr1D* arr2D;
typedef tuple<arr1D, int> solution;

void readTestFile (const string& path, arr2D& graph, int& n);
void swap (int& x, int& y);
void permutation (const int& n, arr1D a,
                const int& pivot, vector<arr1D>& ponential_sols);
void printSolution (const int& n, const arr1D& a);
int sumCircuit (const arr2D& graph, const int& n, const arr1D& sol);
solution findMinCircuit (const arr2D& graph, const int& n);

int main() {
    arr2D map;
    int n = 0;
    readTestFile("input_5.txt", map, n);
    solution minCircuit = findMinCircuit(map, n);
    printSolution(n-1, get<0>(minCircuit));
    cout << endl << get<1>(minCircuit);
    return 0;
}

void readTestFile (const string& path, arr2D& graph, int& n) {
    fstream fin;
    fin.open(path, ios::in);
    if (fin.is_open()) {
        fin >> n;
        int tmp_i, tmp_j, len_ij;
        graph = new arr1D[n];
        for (size_t i = 0; i < n; i++) {
            graph[i] = new int[n];
            for (size_t j = 0; j < n; j++)
            {
                graph[i][j] = 0;
            }
        }
        while (true) {
            fin >> tmp_i;
            if (tmp_i == -1) {
                break;
            }
            fin >> tmp_j;
            fin >> len_ij;
            graph[tmp_i-1][tmp_j-1] = len_ij;
            graph[tmp_j-1][tmp_i-1] = len_ij;
        }
    }
    return;
}
void swap (int& x, int& y) {
    int tmp = x;
    x = y;
    y = tmp;
}
void permutation (const int& n, arr1D a,
                const int& pivot, vector<arr1D>& ponential_sols) {
    if (pivot == n-1) {
        arr1D sol = new int[n];
        for (size_t i = 0; i < n; i++)
        {
            sol[i] = a[i];
        }
        ponential_sols.push_back(sol);
    }
    else {
        for (size_t i = pivot; i < n; i++) {
            swap(a[pivot], a[i]);
            permutation(n, a, pivot+1, ponential_sols);
            swap(a[pivot], a[i]);
        }
    }
}
void printSolution (const int& n, const arr1D& a) {
    cout << "1" << " ";
    for (size_t i = 0; i < n; i++)
    {
        cout << a[i] + 1<<" ";
    }
    return;
}
int sumCircuit (const arr2D& graph, const int& n, const arr1D& sol) {
    arr1D circuit = new int[n+1];
    circuit[0] = circuit[n] = 0;
    int sum = 0;
    for (size_t i = 1; i < n; i++)
    {
        circuit[i] = sol[i-1];
    }
    
    for (size_t i = 0; i < n; i++)
    {
        if (graph[circuit[i]][circuit[i+1]] == 0)
            return MAX_PATH;
        else {
            sum += graph[circuit[i]][circuit[i+1]];
        }
    }
    return sum;
}
solution findMinCircuit (const arr2D& graph, const int& n) {
    arr1D a = new int[n-1];
    // initializing an array of n cities
    for (size_t i = 0; i < n-1; i++)
    {
        a[i] = i+1;
    }
    // all the permutation of n-1 cites except the city 0
    vector<arr1D> lstSols;
    permutation(n-1, a, 0, lstSols);
    int minPath = MAX_PATH;
    arr1D sol_circuit = nullptr;
    for (size_t i = 0; i < lstSols.size(); i++)
    {
        int tmpSum = sumCircuit(graph, n, lstSols[i]);
        if (tmpSum < minPath) {
            minPath = tmpSum;
            sol_circuit = lstSols[i];
        }
    }
    solution s = make_tuple(sol_circuit, minPath);
    return s;
}