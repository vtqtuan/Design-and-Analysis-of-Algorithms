/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for the Josephus Problem with Decrease
 * And Conquer approach
 * **/
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
typedef queue<int> survivors;
struct JosephusProblem
{
    unsigned int n;
    survivors surs;
};
void readTestFile (const char* path, JosephusProblem& p);
queue<int> killMan(JosephusProblem& p);
int main() {
    JosephusProblem prb;
    readTestFile("input_2.txt", prb);
    queue<int> kill = killMan(prb);
    while (!kill.empty()) {
        cout << kill.front() << " ";
        kill.pop();
    }
    cout << endl << prb.surs.front();
    return 0;
}
void readTestFile (const char* path, JosephusProblem& p) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        fin >> p.n;
        for (int h=0; h<p.n; h+=1) {
            p.surs.push(h+1);
        }
        fin.close();
    }
    return;
}

queue<int> killMan(JosephusProblem& p) {
    int mark = 1;
    queue<int> killList;
    while (p.surs.size() != 1) {
        if (mark) {
            int x = p.surs.front();
            p.surs.pop();
            p.surs.push(x);
            mark=0;
        }
        else {
            int x = p.surs.front();
            killList.push(x);
            p.surs.pop();
            mark=1;
        }
    }
    return killList;
}