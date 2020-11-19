/*********************************************************************  
*   Author: Quang-Tuan Vo-Tran                                       *
*   This source code was implemented for The change-making problem   *
*   with brute force approach                                        *
**********************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
struct ChangeMaking
{
    /* data */
    int sumOfCoins = 0; // Sum of all coin*number
    int n = 0; // number of value to change
    int numberOfCoins = 0; // number of coins after changing
    int* components = nullptr; // List of all components
    int* numbers = nullptr; // List of all numbers corresponding to values of coins
};
void readTestFile (const string& path, ChangeMaking& prob);
void printSolution(const ChangeMaking& prob);
void updateSol (int* sol, int* tmpSol, const int& n);
void recurse (int index, ChangeMaking& prob, int totalNums, int tmpSum, int* tmpNums);
void solveChangeMaking(ChangeMaking& prob);
int main() {
    ChangeMaking prob;
    vector<string> lstTestFile = {"input_3.txt"};
    readTestFile(lstTestFile[0], prob);
    solveChangeMaking(prob);
    printSolution(prob);
    return 0;
}
void readTestFile (const string& path, ChangeMaking& prob)
{
    fstream fin;
    fin.open(path, ios::in);
    if (!fin.is_open()) return;
    vector<int> readRes;
    int read;
    while (fin >> read)
    {
        readRes.push_back(read);
    }
    int length = readRes.size();
    prob.sumOfCoins = readRes[length-1];
    prob.numberOfCoins = prob.sumOfCoins;
    prob.components = new int[length-1];
    prob.numbers = new int[length-1];
    for (size_t i = 0; i < length-1; i++)
    {
        prob.components[i] = readRes[i];
        prob.numbers[i] = 0;
    }
    prob.n = length-1;
    fin.close();
}
void printSolution(const ChangeMaking& prob)
{
    for (size_t i = 0; i < prob.n-1; i++)
    {
        cout << prob.components[i] <<": "<< prob.numbers[i] <<endl;
    }
    cout << prob.components[prob.n-1] <<": "<< prob.numbers[prob.n-1];
    return;
}

void updateSol (int* sol, int* tmpSol, const int& n) {
    /* Update the solution of this problem*/
    for (size_t i = 0; i < n; i++)
    {
        sol[i] = tmpSol[i]; 
    }
}
void recurse (int index, ChangeMaking& prob, int totalNums, int tmpSum, int* tmpNums) {
    for (size_t i = 0; i <= int(prob.sumOfCoins/prob.components[index]); i++)
    {
        totalNums += i;
        tmpNums[index] = i;
        tmpSum += prob.components[index]*i;
        if (tmpSum == prob.sumOfCoins) {
            if (totalNums < prob.numberOfCoins) {
                updateSol(prob.numbers, tmpNums, prob.n);
            }
        }
        if (index < prob.n-1){
            recurse(index+1, prob, totalNums, tmpSum, tmpNums);
        }
        if (tmpSum < prob.sumOfCoins){
            totalNums -= i;
            tmpSum -= prob.components[index]*i;
        }
    }
}
void solveChangeMaking(ChangeMaking& prob) {
    int totalNums = 0;
    int tmpSum = 0;
    int* tmpNums = new int[prob.n];
    recurse(0, prob, totalNums, tmpSum, tmpNums);
}