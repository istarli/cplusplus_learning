#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <array>
#include <unordered_set>
using namespace std;

class Solution {
public:
    struct Point{
        int i_;
        int j_;
        int n_;
        Point() : i_(0), j_(0), n_(0) {}
        Point(int i, int j, int n) : i_(i), j_(j), n_(n) {}
        bool operator==(const Point& obj) const{
            return (i_ == obj.i_ && j_ == obj.j_ && n_ == obj.n_);
        }
        bool valid(vector<vector<bool>>& flag){
            return i_ < n_ && j_ < n_ && !flag[i_][j_];
        }
        int get(vector<vector<int>>& matrix){
            return matrix[i_][j_];
        }
    };
    struct PointHash{
        size_t operator()(const Point& p) const{
            return p.i_ * p.n_ + p.j_;
        }
    };    
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        size_t n = matrix.size();
        vector<vector<bool>> visited(n,vector<bool>(n,false));
        unordered_set<Point,PointHash> s;
        visited[0][0] = true;
        s.insert(Point(0,0,n));
        int step = 1, res = matrix[0][0];
        while(step < k && !s.empty()){
            Point next(n-1,n-1,n);
            auto s_tmp = s;
            for(auto& p : s_tmp){
                Point pi(p.i_+1,p.j_,n);
                Point pj(p.i_,p.j_+1,n);
                bool down = pi.valid(visited),right = pj.valid(visited);
                bool flag = true;
                Point p_tmp;
                if(down && left)
                    p_tmp = pi.get(matrix) < pj.get(matrix) ? pi : pj;
                else if(down)
                    p_tmp = pi;
                else if(right)
                    p_tmp = pj;
                else{
                    s.erase(p);
                    flag = false;
                }
                if(flag && p_tmp.get(matrix) < next.get(matrix)){
                    next = p_tmp;
                }
            }
            s.insert(next);
            res = next.get(matrix);
            ++step;
        }
        return res;
    }
};

int main()
{
    vector<vector<int>> v = {
       { 3,  8,  8},
       { 3,  8,  8},
       { 3,  9, 13}     
    };
    int k = 8;
    while(cin >> k)
        cout << Solution().kthSmallest(v,k) << endl;

    return 0;
}