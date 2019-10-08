#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

/*
1 2 3
4 5 6
7 8 9
-> 1 4 7 8 9 6 3 2 5
*/

void sendFruits(const vector<vector<int>> &grid)
{
    if (grid.empty() || grid[0].empty())
        return;
    int left = -1, right = grid[0].size(), top = -1, bottom = grid.size();
    while (left + 1 < right && top + 1 < bottom)
    {
        for (int i = top + 1; i < bottom; ++i)
        {
            cout << grid[i][left + 1] << " ";
        }
        for (int j = left + 2; j < right; ++j)
        {
            cout << grid[bottom - 1][j] << " ";
        }
        if (left + 2 < right)
        {
            for (int i = bottom - 2; i > top; --i)
            {
                cout << grid[i][right - 1] << " ";
            }
        }
        if (top + 2 < bottom)
        {
            for (int j = right - 2; j > left + 1; --j)
            {
                cout << grid[top + 1][j] << " ";
            }
        }
        top++, bottom--, left++, right--;
    }
    cout << endl;
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            scanf("%d", &grid[i][j]);
        }
    }
    sendFruits(grid);
    return 0;
}