/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for the Knight's tour problem with
 * backtracking approach.
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
using namespace std;
vector<int> stepRow = {2, 1, -1, -2, -2, -1, 1, 2};
vector<int> stepCol = {1, 2, 2, 1, -1, -2, -2, -1};
struct Cell
{
    int row, col;
    int step;
    Cell(const int& r, const int& c, const int& s) {
        row = r;
        col = c;
        step = s;
    }
    friend ostream& operator<< (ostream& os, const Cell& c) {
        os << "(" << c.row << "," << c.col << ")";
        return os;
    }
};
struct compareCell {
    bool operator() (const Cell& lhs, const Cell &rhs) {
        return (lhs.step < rhs.step);
    }
};
typedef set<Cell, compareCell> solution;
typedef vector<int> row;
typedef vector<row> chessBoard;

void readTestFile (const string& path, chessBoard& cb, int& length);
void copySolution (const chessBoard& cb, solution& sol);
void solveKnightTour (const int& i, const int& r, 
                    const int& c, const int& length, 
                    chessBoard& cb, vector<solution>& sols);
void printSolution (const vector<solution>& lst_sols);
int main() {
    chessBoard prob;
    int n = 0;
    vector<solution> lst_sols;
    readTestFile("input_2.txt", prob, n);
    prob[0][0] = 1;
    solveKnightTour(2, 0, 0, n, prob, lst_sols);
    printSolution(lst_sols);
    return 0;
}
void readTestFile (const string& path, chessBoard& cb, int& length) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        fin >> length;
        for (size_t i = 0; i < length; i++)
        {
            row tmp(length, 0);
            cb.push_back(tmp);
        }
    }
}
void copySolution (const chessBoard& cb, solution& sol) {
    for (size_t i = 0; i < cb.size(); i++)
    {
        for (size_t j = 0; j < cb[i].size(); j++)
        {
            Cell tmp(i, j, cb[i][j]);
            sol.insert(tmp);
        }
    }
}
void solveKnightTour (const int& i, const int& r, 
                    const int& c, const int& length, 
                    chessBoard& cb, vector<solution>& sols) {
    for (int k = 0; k < 8; k++) {
        int u = r + stepRow[k];
        int v = c + stepCol[k];
        if ((u >= 0 && u <= length-1) 
            && (v >= 0 && v <= length-1) 
            && cb[u][v] == 0) {
                cb[u][v] = i;
                if (i == length*length) {
                    solution sol;
                    copySolution(cb, sol);
                    sols.push_back(sol);
                }
                else {
                    solveKnightTour(i+1, u, v, length, cb, sols);
                }
                cb[u][v] = 0;
        }
    }
}

void printSolution (const vector<solution>& lst_sols) {
    cout << lst_sols.size() << endl;
    for (size_t i = 0; i < lst_sols.size(); i++)
    {
        set<Cell, compareCell>::iterator itr;
        set<Cell, compareCell>::iterator last = lst_sols[i].end();
        last--;
        for (itr = lst_sols[i].begin(); itr != last; itr++) {
            cout << *itr << ", ";
        }
        cout << *last;
        cout << endl;
    }
}