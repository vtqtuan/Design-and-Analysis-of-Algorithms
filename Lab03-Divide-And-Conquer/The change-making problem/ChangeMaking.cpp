/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for the change making problem with
 * divide and conquer approach in upgraded version
 * **/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
struct ChangeMaking {
    vector<int> coins;
    vector<int> num_coins;
    int money;
    friend ostream& operator<< (ostream& os, const ChangeMaking& p) {
        for (int i=0; i<p.coins.size(); i+=1) {
            cout << p.coins[i] << ": " << p.num_coins[i] << endl;
        }
        return os;
    }
};
void readTestFile (const char* path, ChangeMaking& p);

int moneyChange (ChangeMaking& p, vector<int>& tempRes, int money, int step);
int main() {
    ChangeMaking prb;
    readTestFile("input_5.txt", prb);
    vector<int> tmpSol (prb.coins.size(), 0);
    moneyChange(prb, tmpSol, prb.money, 0);
    cout << prb;

    return 0;
}
void readTestFile (const char* path, ChangeMaking& p) {
    fstream fin;
    fin.open(path);
    while (fin.is_open()) {
        string line = "test";
        while (!fin.eof()) {
            getline(fin, line, '\n');
            stringstream ss(line);
            string token;
            while (ss >> token) {
                p.coins.push_back(atoi(token.c_str()));
            }
        }
        p.money = p.coins[p.coins.size()-1];
        p.coins.pop_back();
        vector<int> v(p.coins.size(), 0);
        p.num_coins = v;
        fin.close();
    }
    return;
}

int moneyChange (ChangeMaking& p, vector<int>& tempRes, int money, int step) {
for (int i = 0; i < p.coins.size(); i++)
        if (p.coins[i] == money){
            tempRes = vector<int>(p.coins.size(), 0);
            tempRes[i] = 1;
            return 1;
        }
    int minCoins = money;
    vector<int> res = vector<int>(p.coins.size(), 0);
    res[p.coins.size() - 1] = money;
    vector<int> tempResult;
    for (int i = 0; i < p.coins.size(); i++)
        if (money > p.coins[i]) {
            int temp = 1 + moneyChange(p, tempResult, money - p.coins[i], step);
            tempResult[i] += 1;
            if (temp < minCoins) {
                res = tempResult;
                minCoins = temp;
            }
        }
    tempRes = res;
    p.num_coins = tempRes;
    return minCoins;
}