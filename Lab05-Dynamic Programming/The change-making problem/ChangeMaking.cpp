/**
 * @file ChangeMaking.cpp
 * @author Quang-Tuan Vo-Tran (18127248@student.hcmus.edu.vn)
 * @brief This code implemented for solving the change making problem with
 * dynamic programming technique
 * @version 0.1
 * @date 2020-12-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
struct ChangeMaking
{
    vector<int> coins;
    vector<int> res;
    vector<int> sol;
    int money;

    friend ostream& operator<< (ostream& os, const ChangeMaking& p);
};
void readTestFile (const char* path, ChangeMaking& p);
int changeCoinDP ( ChangeMaking& p);
int findCoin (const vector<int>& coins, const int& c);
void saveSol(vector<int> res, int pos, ChangeMaking& p);
int main() {
    ChangeMaking prb;
    readTestFile("input_2.txt", prb);
    changeCoinDP(prb);
    saveSol(prb.res, prb.money, prb);
    for (int i=prb.sol.size()-1; i>=0; i-=1) {
        cout << prb.coins[i] <<": "<<prb.sol[i] << endl;
    }
    return 0;
}
ostream& operator<< (ostream& os, const ChangeMaking& p) {
    int n = p.coins.size();
    for (int i=0; i<n; i+=1) {
        os << p.coins[i] <<" ";
    }
    os << endl << p.money;
    return os;
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
        vector<int> v(p.money+1, 0);
        p.res = v;
        sort(p.coins.begin(), p.coins.end());
        vector<int> t(p.coins.size(), 0);
        p.sol = t;
        fin.close();
    }
    return;
}
int findCoin (const vector<int>& coins, const int& c) {
    for (int i=0; i<coins.size(); i+=1) {
        if (coins[i] == c) {
            return i;
        }
    }
    return -1;
}
void saveSol(vector<int> res, int pos, ChangeMaking& p) {
    //cout << pos - res[pos] << " ";
    int i = findCoin(p.coins, pos-res[pos]);
    p.sol[i] += 1;
    if (res[pos] == 0)
        return;
    saveSol(res, res[pos], p);
}

int changeCoinDP ( ChangeMaking& p) {
    vector<int> C(p.money+1, 0);
    for (int cents=1; cents<=p.money; cents+=1) {
        int minCoins = cents;
        for (int i=0; i<p.coins.size(); i+=1) {
            if (p.coins[i] > cents) {
                continue;
            }
            if (C[cents-p.coins[i]] + 1 < minCoins) {
                minCoins = C[cents - p.coins[i]] + 1;
                p.res[cents] = cents - p.coins[i];
            }
        }
        C[cents] = minCoins;
    }
    return C[p.money];
}