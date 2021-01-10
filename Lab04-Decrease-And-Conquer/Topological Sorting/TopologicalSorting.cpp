/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implemented for the Topological Sorting with decrease
 * and conquer approach
 * **/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
typedef vector<int> adjacent;
struct Graph {
    unsigned int nVertices;
    vector<adjacent> grp;
    friend ostream& operator<< (ostream& os, const Graph& g) {
        for(int i=0; i<g.nVertices; i+=1) {
            for (int j=0; j<g.nVertices; j+=1) {
                os << g.grp[i][j] << '\t';
            }
            os << endl;
        }
        return os;
    }
};
void readTestFile (const char* path, Graph& inp);
void topologicalSort (const Graph& inp);
int main() {
    Graph prb;
    readTestFile("input_1.txt", prb);
    topologicalSort(prb);
    return 0;
}
void readTestFile (const char* path, Graph& inp) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        fin >> inp.nVertices;
        vector<adjacent> init(inp.nVertices, adjacent(inp.nVertices, 0));
        inp.grp = init;
        string line =" ";
        while (line != "0")
        {
            getline(fin, line, '\n');
            if (line != "0") {
                stringstream ss(line);
                string token;
                adjacent adj;
                while (ss >> token) {
                    adj.push_back(atoi(token.c_str()));
                }
                for (int i=1; i<adj.size(); i+=1) {
                    inp.grp[adj[0]-1][adj[i]-1] = -1;
                    inp.grp[adj[i]-1][adj[0]-1] = 1;
                }
            }
        }
        fin.close();
    }
    return;
}
void topologicalSort (const Graph& inp) {
    vector<int> indegree(inp.nVertices, 0);
    queue<int> Q;
    for (int u=0; u<inp.nVertices; u+=1) {
        for (int v=0; v<inp.nVertices; v+=1) {
            if (inp.grp[u][v] == -1) {
                indegree[u] += 1;
            }
        }
    }
    for (int u=0; u<indegree.size(); u+=1) {
        if (indegree[u] == 0) {
            Q.push(u);
        }
    }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        cout << u+1 << " ";
        for (int v=0; v<inp.nVertices; v+=1) {
            if (inp.grp[u][v] == 1) {
                if (--indegree[v]==0) {
                    Q.push(v);
                }
            }
        }
    }
}