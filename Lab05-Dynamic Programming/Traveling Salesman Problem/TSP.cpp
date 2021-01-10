/**
 * @file TSP.cpp
 * @author Quang-Tuan Vo-Tran (18127248@student.hcmus.edu.vn)
 * @brief This code was implemented for Traveling Salesman Problem (TSP) with
 * dynamic programming technique.
 * @version 0.1
 * @date 2021-01-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <climits>
#include <set>
#include <map>
#include <iterator>
#include <math.h>
#define INF 100000
using namespace std;
//data structure represents a adjacency matrix
typedef vector<vector<int>> Graph;
void displayGraph (const Graph& G) {
    for (int i=0; i<G.size(); i++) {
        for (int j=0; j<G.size(); j++) {
            cout << G[i][j] << "\t";
        }
        cout << endl;
    }
}
bool readTestFile (const char* path, Graph& G) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        int n_vertices = 0;
        fin >> n_vertices;
        // Initialize the graph. If G[i][j] == INFINITY: there isn't no edge
        // between vertex i and vertex j.
        G = Graph(n_vertices, vector<int>(n_vertices, INF));
        int v_i, v_j, len_ij;
        while (true) {
            fin >> v_i;
            if (v_i == -1) {
                break;
            }
            fin >> v_j;
            fin >> len_ij;
            G[v_i-1][v_j-1] = G[v_j-1][v_i-1] = len_ij;
        }
        fin.close();
        return true;
    }
    return false;
}
void generateSubset (const set<int>& superSet, map<int, set<int>>& res) {
    int supSetLength = superSet.size();
    int count = pow(2, supSetLength);
    for (int i = 0; i<count; i++) {
        set<int> subSet;
        set<int>::iterator itr = superSet.begin();
        for (int j = 0; j < supSetLength; j++) {
            if ((i & (1 << j)) != 0) {
                subSet.insert(*itr);
                //cout << *itr <<" ";
            }
            itr++;
        }
        res.insert(pair<int, set<int>>(i, subSet));
        //cout << subSet.size() << " ";
        //cout << endl;
    }
}
map<int, set<int>> createMap (const set<int>& superSet) {
    /**
     * @brief Create a map between length of subset and
     * the subset respectively.
     * @param a super set
     * @return a map with key:value, key is subset's length, 
     * value is set.
     */
    map<int, set<int>> res;
    generateSubset(superSet, res);
    return res;
}
int keyOfValue (const map<int, set<int>>& dict, const set<int>& val) {
    /**
     * @brief Return key of a value (set) in a map
     * @param dict Map with key:value (int:set<int>)
     * @param val value need fo return key (set<int>)
     * @return Key of Val (int)
     */
    map<int, set<int>>::const_iterator itr = dict.begin();
    for (itr; itr != dict.end(); itr++) {
        if (itr->second == val) {
            return itr->first;
        }
    }
    return -1; // not found
}
void displayMap (const map<int, set<int>>& dict) {
    map<int, set<int>>::const_iterator itr = dict.begin();
    for (itr; itr != dict.end(); itr++) {
        cout << "key: " << itr->first << endl;
        set<int>::iterator set_itr = itr->second.begin();
        cout << "value: ";
        for (set_itr; set_itr != itr->second.end(); set_itr++) {
            cout << *set_itr <<" ";
        }
        cout << endl;
    }
    return;
}
void TSP_Tour (const vector<vector<int>>& P, set<int> vertices, const map<int, set<int>>& dict) {
    int k = 1;
    while (vertices.size() != 0) {
        int idOfA = keyOfValue (dict, vertices);
        k = P[k][idOfA];
        cout << k+1 << " ";
        vertices.erase(k);
    }
}
int solveTSP_DP (const Graph& G) {
    int n_vertices = G.size();
    int n_subset = pow(2, n_vertices-1);
    vector<vector<int>> D(n_vertices, vector<int>(n_subset, 0));
    vector<vector<int>> P(n_vertices, vector<int>(n_subset, 0));

    // Set of n cities (not include the begin vertex (v1))
    set<int> vertices;
    for (int i=1; i<n_vertices; i++) {
        vertices.insert(i);
    }

    map<int, set<int>> map_subsets = createMap(vertices);

    //Set up for A is empty
    for (int i=1; i<n_vertices; i++) {
        D[i][0] = G[i][0];
    }

    // with k elements in A (size of A)
    for (int k = 1; k<= n_vertices-2; k++) {
        map<int, set<int>>::iterator itr;
        for (itr = map_subsets.begin(); itr != map_subsets.end(); itr++) {
            //choose the A with k elements to run
            if (itr->second.size() == k) {
                // choose the element vi with i != the first vertex and vi not in A
                for (int i=1; i<n_vertices; i++) {
                    bool is_in = itr->second.find(i) != itr->second.end();
                    // if vi not in A ->return false
                    if (!is_in) {
                        set<int>::iterator A_itr = itr->second.begin();
                        int temp = INT_MAX;
                        for (A_itr; A_itr != itr->second.end(); A_itr++) {
                            
                            set<int> A_tmp = itr->second;
                            A_tmp.erase(*A_itr);

                            int A_tmp_key = keyOfValue(map_subsets, A_tmp);
                            if (G[i][*A_itr] + D[*A_itr][A_tmp_key] < temp) {
                                D[i][itr->first] = G[i][*A_itr] + D[*A_itr][A_tmp_key];
                                temp = G[i][*A_itr] + D[*A_itr][A_tmp_key];
                                P[i][itr->first] = *A_itr;
                            }
                        }
                        //cout << temp << " ";
                    }
                }
            }
        }
    }
    int idOfRemainVertices = keyOfValue (map_subsets, vertices);
    int tmpCost = INT_MAX;
    for (int j=1; j<n_vertices; j++) {
        set<int> tmpV = vertices;
        tmpV.erase(j);
        int tmpVid = keyOfValue(map_subsets, tmpV);
        if (G[0][j] + D[j][tmpVid] < tmpCost) {
            tmpCost = G[0][j] + D[j][tmpVid];
            D[0][idOfRemainVertices] = tmpCost;
            P[0][idOfRemainVertices] = j;
        }
    }
    cout << D[0][idOfRemainVertices]-INF << endl;
    TSP_Tour(P, vertices, map_subsets);
    return D[0][idOfRemainVertices]-INF;
}


int main() {
    Graph G;
    readTestFile("input_8.txt", G);
    solveTSP_DP(G);

    return 0;
}