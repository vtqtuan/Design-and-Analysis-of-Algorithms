/**
 * Author: Quang-Tuan Vo-Tran
 * This is C++ source code implemented for knapsach problem
 * with brute-force approach
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
struct Item
{
    int weight;
    int value;
    int index;
};

struct KnapSach {
    int capacity;
    int nItems;
    vector<Item> lst;
};
void readTestFile (const string& path, KnapSach& prob);
int calculateSumWeight (const vector<Item>& subSet);
vector<vector<Item>> generateSubSet (const vector<Item>& lst);
vector<Item> solveKnapSach (const KnapSach& prob);
void printSolution (const vector<Item>& sol);
int main() {
    KnapSach kns;
    readTestFile ("input_6.txt", kns);
    vector<Item> solution = solveKnapSach (kns);
    printSolution(solution);
    return 0;
}

void readTestFile (const string& path, KnapSach& prob) {
    fstream fin;
    fin.open(path, ios::in);
    if (fin.is_open()) {
        fin >> prob.capacity;
        fin >> prob.nItems;
        Item read;
        for (size_t i = 0; i < prob.nItems; i++)
        {
            fin >> read.weight >> read.value;
            read.index = i + 1;
            prob.lst.push_back(read);
        }
    }
}

int calculateSumWeight (const vector<Item>& subSet) {
    int sumWeight = 0;
    for (size_t i = 0; i < subSet.size(); i++)
    {
        sumWeight += subSet[i].weight;
    }
    return sumWeight;
}

vector<vector<Item>> generateSubSet (const vector<Item>& lst) {
    vector<vector<Item>> res;
    vector<Item> empty;
    res.push_back(empty);
    for (size_t i = 0; i < lst.size(); i++)
    {
        int len = res.size();
        for (size_t j = 0; j < len; j++) {
            vector<Item> temp(res[j]);
            temp.push_back(lst[i]);
            res.push_back(temp);
        }
    }
    return res;
}

vector<Item> solveKnapSach (const KnapSach& prob) {
    vector<vector<Item>> lstSubSet = generateSubSet(prob.lst);
    int tempSum = 0;
    vector<Item> *sol;
    for (size_t i = 1; i < lstSubSet.size(); i++) {
        int sum = calculateSumWeight(lstSubSet[i]);
        if (sum <= prob.capacity && sum > tempSum) {
            tempSum = sum;
            sol = &lstSubSet[i];
        }
    }
    return *sol;
}

void printSolution (const vector<Item>& sol) {
    if (sol.size() == 0) return;
    int sum = 0;
    for (size_t i = 0; i < sol.size(); i++)
    {
        cout << sol[i].index << " ";
        sum += sol[i].value;
    }
    cout << endl << sum;
}