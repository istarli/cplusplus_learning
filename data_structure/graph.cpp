#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <climits>
#include <algorithm>
using namespace std;

void PrintPath(vector<int> &path);

struct PathNode
{
	int cost;
	int prev;
};

vector<PathNode> __spanning_tree(
	int root, const int MAX,
	vector<vector<int>> &mat,
	function<int(int, int)> func)
{
	int n = mat.size();
	if (n <= 0 || root < 0 || root >= n)
		return {};
	// Init help data
	int v = root;
	vector<bool> flag(n, false);
	vector<PathNode> path(n);
	flag[v] = true;
	for (int i = 0; i < n; ++i)
	{
		path[i].cost = mat[v][i];
		path[i].prev = (mat[v][i] < MAX) ? v : -1;
	}
	path[v].cost = 0;
	path[v].prev = -1;
	// Update help data
	for (int i = 0; i < n; ++i)
	{
		// -> Step 1 : find min-cost-node and assign to v
		int _min = MAX;
		for (int j = 0; j < n; ++j)
		{
			if (!flag[j] && _min > path[j].cost)
			{
				_min = path[j].cost;
				v = j;
			}
		}
		// caution : if no valid min, then return, otherwith cost would overflow
		if (_min == MAX)
			return path;
		// -> Step 2 : update flag-cost-pre by v
		flag[v] = true;
		for (int j = 0; j < n; ++j)
		{
			if (!flag[j])
			{
				// prim: [](int a, int b) { return b;}
				// dijstra: [](int a,b) {return a+b};
				int new_cost = func(path[v].cost, mat[v][j]);
				if (path[j].cost > new_cost)
				{
					path[j].cost = new_cost;
					path[j].prev = v;
				}
			}
		}
	}
	return path;
};

int Prim(vector<vector<int>> &mat, const int MAX)
{
	auto spath = __spanning_tree(0, MAX, mat, [](int a, int b) { return b; });
	int res = 0;
	for (auto &pnode : spath)
	{
		res += (pnode.cost < MAX) ? pnode.cost : 0;
	}
	return res;
}

vector<PathNode> Dijstra(vector<vector<int>> &mat, int src, int MAX)
{
	return __spanning_tree(src, MAX, mat, [](int a, int b) { return a + b; });
};

vector<int> __find_path(vector<PathNode> &spath, int src, int dst)
{
	int n = spath.size();
	if (n <= 0 || src >= n || src < 0 || dst >= n || dst < 0)
		return {};

	int pre = dst;
	vector<int> path;
	while (pre != -1 && pre != src)
	{
		path.push_back(pre);
		pre = spath[pre].prev;
	}
	path.push_back(pre);
	reverse(path.begin(), path.end());
	return path;
}

void PrintPath(vector<int> &path)
{
	for (auto &x : path)
		cout << x << "->";
	cout << "end" << endl;
}

int main(int argc, char *argv[])
{
	const int MAX = 1000000;
	/*
		0--(10)--1
		|		 |
	   (5)		(5)
		|		 |
		3--(5)---2
	*/
	vector<vector<int>> mat = {
		//0--1--2--3
		{0, 10, MAX, 5}, // 0
		{10, 0, 5, MAX}, // 1
		{MAX, 5, 0, 5},  // 2
		{5, MAX, 5, 0},  // 3
	};

	cout << Prim(mat, MAX) << endl;

	auto res = Dijstra(mat, 0, MAX);
	auto path = __find_path(res, 0, 1);
	PrintPath(path);
	cout << res[1].cost << endl;

	return 0;
}
