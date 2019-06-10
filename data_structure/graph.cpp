#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <climits>
#include <algorithm>
using namespace std;

void PrintPath(vector<int>& path);

vector<vector<int>> __spanning_tree(
	int root, int block, 
	vector<vector<int>>& mat, 
	function<int(int&,int&)> func)
{
	int n = mat.size();
	if(n <= 0 || root < 0 || root >= n)
		return vector<vector<int>>();
	// Init help data
	int v = root;
	vector<bool> flag(n,false);
	vector<int> cost(n,INT_MAX);
	vector<int> prev(n,-1);
	flag[v] = true;
	for(int i = 0; i < n; ++i){
		cost[i] = (mat[v][i] != block) ? mat[v][i] : INT_MAX;
		prev[i] = (cost[i] != INT_MAX) ? v : -1;
	}
	cost[v] = 0;
	prev[v] = -1;
	// Update help data
	for(int i = 0; i < n; ++i){
		// -> Step 1 : find min-cost-node and assign to v
		int _min = INT_MAX;
		for(int j = 0; j < n; ++j){
			if(!flag[j] && _min > cost[j]){
				_min = cost[j];
				v = j;
			}
		}
		// caution : if no valid min, then return, otherwith cost would overflow
		if(_min == INT_MAX)
			return {cost,prev};
		// -> Step 2 : update flag-cost-pre by v
		flag[v] = true;
		for(int j = 0; j < n; ++j){
			if(!flag[j]){
				int new_cost = (mat[v][j] != block) ? func(cost[v],mat[v][j]) : INT_MAX;
				if(cost[j] > new_cost){
					cost[j] = new_cost;
					prev[j] = v;
				}
			}
		}
	}
	return {cost,prev};
};

vector<int> __find_path(vector<int>& prev, int src, int dst)
{
	int n = prev.size();
	if(n <= 0 || src >= n || src < 0 || dst >= n || dst < 0)
		return vector<int>();

	int pre = dst;
	vector<int> path;
	while(pre != -1 && pre != src){
		path.push_back(pre);
		pre = prev[pre];
	}
	path.push_back(pre);
	reverse(path.begin(),path.end());
	return path;
}

vector<int> FindPath(vector<int>&pre, int src, int dst)
{
	auto path1 = __find_path(pre,src,dst);
	if(path1.empty() || path1[0] == src)
		return path1; /* father->src->dst */
	
	auto path2 = __find_path(pre,dst,src);
	if(path2.empty() || path2[0] == dst){
		reverse(path2.begin(),path2.end());
		return path2; /* father->dst->src */
	}
	/* father->dst(path1) + father->src(path2) => src->father->dst */
	// -> Step1 : find k, k is the idx of the closed father for src and dst
	int k = 0, len1 = path1.size(), len2 = path2.size();
	for(; k < len1 && k < len2 && path1[k] == path2[k]; ++k);
	--k; 
	// -> Step2 : add src->father and father->dst
	int j = 0;
	vector<int> res(len1+len2-2*k-1);
	for(int i = len2-1; i >= k; res[j++] = path2[i--]);
	for(int i = k+1; i < len1; res[j++] = path1[i++]);

	return res;
}

vector<vector<int>> Prim(vector<vector<int>>& mat, int block, int src=0)
{
	return __spanning_tree(src,block,mat,[](int& a,int& b){return b;});
}

vector<vector<int>> Dijstra(vector<vector<int>>& mat, int src, int block)
{
	return __spanning_tree(src,block,mat,[](int& a,int& b){return a+b;});
};

void PrintMatrix(string name,vector<vector<int>>& mat)
{
	cout << name << " <cost,prev>" << endl;
	for(auto& v : mat){
		for(auto& x : v)
			cout << x << " ";
		cout << endl;
	}
}

void PrintPath(vector<int>& path)
{
	for(auto& x : path)
		cout << x << "->";
	cout << "end" << endl;
}

int main(int argc,char *argv[])
{
	vector<vector<int>> mat = {
		//0--1--2--3  
		{ 0,10,-1, 5}, // 0
		{10, 0, 5,-1}, // 1
		{-1, 5, 0, 5}, // 2
		{ 5,-1, 5, 0}, // 3
	};

	auto res = Prim(mat,-1);
	PrintMatrix("Prim",res);
	auto path = FindPath(res[1],1,0);
	PrintPath(path);

	res = Dijstra(mat,0,-1);
	PrintMatrix("Dijstra",res);
	path = FindPath(res[1],2,1);
	PrintPath(path);

 	return 0;
}
