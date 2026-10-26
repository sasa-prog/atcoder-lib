#include <bits/stdc++.h>
#define ll long long
using namespace std;

// 二次元幾何
struct Point {
    ll x, y;
    int pos() const {
    if (y < 0) return -1;
    if (y == 0 && 0 <= x) return 0;
        return 1;
    }
};
// 位置ベクトルの内積を計算する
ll dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}
// 位置ベクトルの外積を計算する
ll cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}
// a-bを計算する
Point operator-(Point a, Point b) {
    return {a.x - b.x, a.y - b.y};
}
// a+bを計算する
Point operator+(Point a, Point b) {
    return {a.x + b.x, a.y + b.y};
}


// aからbに行く場合、cがどちら側にあるか
// 1の場合、左側にある。
// 0の場合直線AB上にある。
// -1の場合直線ABの右側にある
int ccw(Point a, Point b, Point c) {
    ll v = cross(b - a, c - a);

    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}
// pが線分ab上にあるかどうか
bool on_segment(Point a, Point b, Point p) {
    return cross(b - a, p - a) == 0 &&
           min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}
// 線分abとcdが交差するかどうか
bool intersect(Point a, Point b, Point c, Point d) {
    int abc = ccw(a, b, c);
    int abd = ccw(a, b, d);
    int cda = ccw(c, d, a);
    int cdb = ccw(c, d, b);

    // 一般の場合
    if (abc * abd < 0 && cda * cdb < 0)
        return true;

    // 端点や重なり
    if (abc == 0 && on_segment(a, b, c)) return true;
    if (abd == 0 && on_segment(a, b, d)) return true;
    if (cda == 0 && on_segment(c, d, a)) return true;
    if (cdb == 0 && on_segment(c, d, b)) return true;

    return false;
}

void ArgumentSort(vector<Point> &v) {
  sort(begin(v), end(v), [](Point a, Point b) {
    if (a.pos() != b.pos()) return a.pos() < b.pos();
    return cross(a, b) > 0;
  });
}
