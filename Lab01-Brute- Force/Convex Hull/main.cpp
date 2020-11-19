/**
 * Author: Quang-Tuan Vo-Tran
 * This code was implement for the Comvex-hull problem, with
 * the computeAngle Brute-Force Approach
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <iterator>
#include <set>
#include <tuple>
#define PI 3.1415
using namespace std;
struct Point
{
    float x, y;
    friend ostream& operator<< (ostream& os, const Point& p) {
        os << "("<< p.x << "," << p.y << ")";
        return os;
    }
    
};
struct comparePoints {
    bool operator() (const Point& lhs, const Point& rhs) {
        return (lhs.y < rhs.y) || ((!(lhs.y < rhs.y)) && (lhs.x < rhs.x));
    }
};
struct ConvexHull
{
    set <Point, comparePoints> setPoints;
    set <Point, comparePoints> setSol;
};
void readTestFile (const string& path, ConvexHull& prob);
void printSolution (const ConvexHull& prob);
float computeAngle (const Point& from, const Point& to);
tuple<Point, float> findNextExtremePoint(ConvexHull& prob, Point& cur, float& curAngle);
void solveConvexHull (ConvexHull& prob);

int main() {
    ConvexHull prob;
    readTestFile("input_4.txt", prob);
    solveConvexHull(prob);
    printSolution(prob);
    return 0;
}

void readTestFile (const string& path, ConvexHull& prob) {
    fstream fin;
    fin.open(path, ios::in);
    if (!fin.is_open())
        return;
    int n;
    fin >> n;
    for (size_t i = 0; i < n; i++)
    {
        Point t;
        fin >> t.x;
        fin >> t.y;
        prob.setPoints.insert(t);
    }
    return;
}

void printSolution (const ConvexHull& prob)
{
    set <Point, comparePoints>::iterator itr;
    for (itr=prob.setSol.begin(); itr != prob.setSol.end(); ++itr) {
        cout << *itr << " ";
    }
    return;
}

float computeAngle (const Point& from, const Point& to) {
    float angle = atan2(to.y - from.y, to.x - from.x);
    if (angle < 0)
        angle += 2 * PI;
    return angle;
}

tuple<Point, float> findNextExtremePoint(ConvexHull& prob, Point& cur, float& curAngle) {
    float minAngle = 2*PI;
    set <Point, comparePoints>::iterator itr;
    Point nextPoint;
    for (itr=prob.setPoints.begin(); itr != prob.setPoints.end(); itr++) {
        if (!((*itr).x == cur.x && (*itr).y == cur.y)) {
            float angle = computeAngle(cur, *itr);
            if (angle < minAngle && angle >= curAngle) {
                nextPoint = *itr;
                minAngle = angle;
            }
        }
    }
    tuple <Point, float> res = make_tuple(nextPoint, minAngle);
    return res;
}
void solveConvexHull (ConvexHull& prob) {
    Point first = *prob.setPoints.begin();
    prob.setSol.insert(first);
    Point cur = first;
    tuple <Point, float> res = make_tuple(first, 0);
    while (true) {
        res = findNextExtremePoint(prob, cur, get<1>(res));
        if (first.x == get<0>(res).x && first.y == get<0>(res).y) {
            break;
        }
        prob.setSol.insert(get<0>(res));
        cur = get<0>(res);
    }
}