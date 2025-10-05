// Erect the Fence
// You are given an array trees where trees[i] = [xi, yi] represents the location of a tree in the garden.

// You are asked to fence the entire garden using the minimum length of rope as it is expensive. The garden is well fenced only if all the trees are enclosed.

// Return the coordinates of trees that are exactly located on the fence perimeter in sorted order.

// Constraints:

// 1 <= points.length <= 3000

// points[i].length == 2

// 0 <= xi, yi <= 100

// All the given points are unique.

// Example :



// Input: points = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
 
// Output: [[1,1],[2,0],[2,4],[3,3],[4,2]]

#include<bits/stdc++.h>
using namespace std;

class ConvexHull{

    public:
    struct Point {
        int x, y;
        bool operator < (Point P) const {
            if (x == P.x) return y < P.y;
            else return x < P.x;
        }
        bool operator == (Point P) const {
            return (x == P.x && y == P.y);
        }
    };

    bool cw(Point a, Point b, Point c) {
        return a.x * (c.y - b.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y) > 0;
    }

    bool ccw(Point a, Point b, Point c) {
        return a.x * (c.y - b.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y) < 0;
    }

    bool cll(Point a, Point b, Point c) {
        return a.x * (c.y - b.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y) == 0;
    }

    vector<Point> points;
    
    void insertPoints(int x, int y){
        points.push_back({x,y});
    }
    
    vector<Point> convex_hull_exclude_collinear_points() {
        if (points.size() <= 2) return points;

        sort(points.begin(), points.end());

        vector<Point> up, down;
        Point first = points[0], last = points.back();

        up.push_back(first); down.push_back(first);

        for (int i = 1; i < points.size(); i++) {
            if (i == points.size() - 1 || cw(first, points[i], last)) {
                // up set

                while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], points[i])) {
                    up.pop_back();
                }

                up.push_back(points[i]);

            }
            if (i == points.size() - 1 || ccw(first, points[i], last)) {
                // down set

                while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], points[i])) {
                    down.pop_back();
                }

                down.push_back(points[i]);

            }
        }

        points.clear();
        for (int i = 0; i < up.size(); i++) {
            points.push_back(up[i]);
        }
        for (int i = 0; i < up.size(); i++) {
            points.push_back(down[i]);
        }

        sort(points.begin(), points.end());

        points.resize(unique(points.begin(), points.end()) - points.begin());

        return points;
    }

    vector<Point> convex_hull_include_collinear_points() {
        
        vector<Point> ch_points=points;
        if (ch_points.size() <= 2) return ch_points;

        sort(ch_points.begin(), ch_points.end());

        vector<Point> up, down;
        Point first = ch_points[0], last = ch_points.back();
        
        cout<<"first ("<<first.x<<", "<<first.y<<")"<<endl;
        cout<<"last ("<<last.x<<", "<<last.y<<")"<<endl;

        up.push_back(first); down.push_back(first);

        for (int i = 1; i < ch_points.size(); i++) {
            printPoint(ch_points[i]);
            if (i == ch_points.size() - 1 || !ccw(first, ch_points[i], last)) {
                // up set
                printf("up\n");
                while (up.size() >= 2 && ccw(up[up.size() - 2], up[up.size() - 1], ch_points[i])) {
                    Point back=up.back();
                    printf("pop up\n");
                    printPoint(back);
                    up.pop_back();
                }

                up.push_back(ch_points[i]);

            }
            if (i == ch_points.size() - 1 || !cw(first, ch_points[i], last)) {
                // down set

                printf("down\n");
                while (down.size() >= 2 && cw(down[down.size() - 2], down[down.size() - 1], ch_points[i])) {
                    Point back=down.back();
                    printf("pop down\n");
                    printPoint(back);
                    down.pop_back();
                }

                down.push_back(ch_points[i]);

            }
        }
        
        printf("up\n");
        printPoints(up);
        printf("down\n");
        printPoints(down);

        ch_points.clear();
        for (int i = 0; i < up.size(); i++) {
            ch_points.push_back(up[i]);
        }
        for (int i = 0; i < down.size(); i++) {
            ch_points.push_back(down[i]);
        }
        
        printf("ch_pts\n");
        printPoints(ch_points);

        sort(ch_points.begin(), ch_points.end());

        ch_points.resize(unique(ch_points.begin(), ch_points.end()) - ch_points.begin());

        return ch_points;
    }
    
    void printPoints(){
        for(int i=0;i<points.size();i++){
            printPoint(points[i]);
        }
    }
    
    void printPoints(vector<Point> pts){
        for(int i=0;i<pts.size();i++){
            printPoint(pts[i]);
        }
    }
    
    void printPoint(Point pt){
        cout<<"("<<pt.x<<", "<<pt.y<<")"<<endl;
    }
};

vector<vector<int>> outerTrees(vector<vector<int>> trees) {
    ConvexHull c;
    
    // Sort first (so duplicates are adjacent)
    sort(trees.begin(), trees.end());

    // Remove duplicates
    //trees.erase(unique(trees.begin(), trees.end()), trees.end());
    
    for(int i=0;i<trees.size();i++){
        c.insertPoints(trees[i][0],trees[i][1]);
    }
    printf("all pt------------\n");
    c.printPoints();
    printf("all pt------------\n");
    
    vector<ConvexHull::Point> point_list=c.convex_hull_include_collinear_points();
    
    sort(point_list.begin(),point_list.end());
    
    vector<vector<int>> ret;
    for(int i=0;i<point_list.size();i++){
        ret.push_back({point_list[i].x, point_list[i].y});
    }
    return ret;
    
}