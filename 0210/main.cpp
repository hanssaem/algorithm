#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int grid[100][100];
int dist[100][100];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int n;

void dijkstra()
{
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    pq.push({grid[0][0], {0, 0}});
    dist[0][0] = grid[0][0];

    while (!pq.empty())
    {
        int cost = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if (dist[x][y] < cost)
        {
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < n)
            {
                if (cost + grid[nx][ny] < dist[nx][ny])
                {
                    dist[nx][ny] = cost + grid[nx][ny];
                    pq.push({cost + grid[nx][ny], {nx, ny}});
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    int test_case;
    int T;
    freopen("input.txt", "r", stdin);
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            string row;
            cin >> row;
            for (int j = 0; j < n; j++)
            {
                grid[i][j] = row[j] - '0';
                dist[i][j] = 1e9;
            }
        }

        dijkstra();
        cout << "#" << test_case << " " << dist[n - 1][n - 1] << "\n";
    }
    return 0;
}