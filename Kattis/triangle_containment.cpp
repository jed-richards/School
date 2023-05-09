#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

#define PI 3.14159265

using namespace std;

struct Point {
    int x, y, val, sum;
    double theta, alpha;

    Point() {
    }

    Point(int x, int y, int val, int X) {
        this->x = x;
        this->y = y;
        this->val = val;
        this->sum = 0;
        this->theta = (atan2(y,x)*180)/PI;
        this->alpha = ((atan2(y, abs(X - x))) * 180) / PI;
    }
};

bool comparePt(Point pt1, Point pt2) {
    return pt1.theta > pt2.theta; 
}

bool checkPt(Point pt1, Point pt2) {
    if (pt2.alpha < pt1.alpha && pt2.y < pt1.y) {
            return true;
    }
    return false;
}

void printPt(Point pt) {
    cout << to_string(pt.x) + " " + to_string(pt.y) + " " + to_string(pt.val) << endl;
}

void printAngles(Point pt) {
    cout << to_string(pt.theta) + " " + to_string(pt.alpha) << endl;
}

void printSum(Point pt) {
    cout << pt.sum << endl;
}

Point getPt(int X) {
    int x, y, val;
    cin >> x >> y >> val;
    Point pt = Point(x, y, val, X);
    return pt;
}

int main() {
    int n, x;
    cin >> n >> x;

    vector<Point> points(n);
    
    for (int i=0; i<n; i++) {
        points[i] = getPt(x);
    }

    vector<Point> unsorted;
    unsorted = points;

    sort(points.begin(), points.end(), comparePt);

    for (int i=0; i<points.size()-1; i++) {
        for (int j=i+1; j<points.size(); j++) {
            if (checkPt(points[i], points[j])) {
                points[i].sum += points[j].val;
            }
        }
    }

    for (Point pt : unsorted) {
        printSum(pt);
    }

    return 0;
}
