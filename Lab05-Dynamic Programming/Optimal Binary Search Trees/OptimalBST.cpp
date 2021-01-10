/**
 * @file OptimalBST.cpp
 * @author Quang-Tuan Vo-Tran (18127248@student.hcmus.edu.vn)
 * @brief This code was implemented for constructing an optimal binary search tree
 * with dynamic programming technique.
 * @version 0.1
 * @date 2021-01-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct Node {
    // default value for left, right and key
    Node* left = nullptr;
    Node* right = nullptr;
    int key = -1;
};
bool readTestFile (const char* path, vector<int>& a, vector<float>& p) {
    fstream fin;
    fin.open(path);
    if (fin.is_open()) {
        int n; fin >> n;
        a = vector<int>(n, 0);
        p = vector<float>(n, 0);
        for (int i=0; i<n; i++) {
            fin >> a[i] >> p[i];
        }
        fin.close();
        return true;
    }
    return false;
}
float sumOfSegment (const vector<float>& a, const int& begin, const int& end) {
    float sum = 0;
    for (int i=begin; i<=end; i++) {
        sum += a[i];
    }
    return sum;
}
void optimalBST (const vector<float>& p, vector<vector<int>>& R) {
    int n = p.size(); // number of keys use for searching
    vector<vector<float>> C(n+2, vector<float>(n+1, 0)); // matrix save the cost
    R = vector<vector<int>>(n+2, vector<int>(n+1, 0)); // matrix use for construct BST

    for (int i=1; i<=n; i++) {
        C[i][i] = p[i-1];
        R[i][i] = i;
    }

    for (int diag=1; diag<n; diag++) {
        for (int i=1; i<= n-diag; i++) {
            int j = i+diag;
            float val = C[i][i-1] + C[i+1][j];
            R[i][j] = i;
            C[i][j] = val + sumOfSegment(p, i-1, j-1);
            for (int t = i+1; t <= j; t++) {
                float tmp = C[i][t-1] + C[t+1][j];
                if (tmp < val) {
                    val = tmp;
                    R[i][j] = t;
                    C[i][j] = val + sumOfSegment(p, i-1, j-1);
                }
            }
        }
    }
}
void DFS_InOrder (Node* root) {
    if (root == nullptr) {
        return;
    }
    DFS_InOrder(root->left);
    cout << root->key << " ";
    DFS_InOrder(root->right);
}
Node* constructTree (const int& i, const int& j, 
                    const vector<vector<int>>& R, const vector<int>& a) {
    int t = R[i][j];
    if (t == 0) {
        return nullptr;
    }
    Node* p = new Node;
    p->key = a[t-1];
    p->left = constructTree(i, t-1, R, a);
    p->right = constructTree(t+1, j, R, a);
    return p;
}
int main() {
    vector<int> a;
    vector<float> p;
    vector<vector<int>> R;
    readTestFile ("input_5.txt", a, p);
    optimalBST(p, R);
    Node* root = constructTree(1, a.size(), R, a);
    if (root != nullptr) {
        cout << root->key << endl;
    }
    DFS_InOrder(root);
    return 0;
}