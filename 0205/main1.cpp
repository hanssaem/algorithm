#include <iostream>
#include <array>
#include <algorithm>
#include <vector>

using namespace std;

using tu = array<long long, 3>;

struct unionFind
{
    int parent[1001];
    int find(int x)
    {
        return parent[x] ? parent[x] = find(parent[x]) : x;
    }
    bool merge(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
        {
            parent[a] = b;
            return true;
        }
        return false;
    }
} union_find;

tu island[1020];

long long square(long long x)
{
    return x * x;
}

long long dist(int a, int b)
{
    return square(island[a][0] - island[b][0]) + square(island[a][1] - island[b][1]);
}

vector<tu> sorted;

void solve()
{
    int n, x, y;
    cin >> n;
    sorted.clear();
    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        union_find.parent[i] = 0;
        island[i][0] = x;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> y;
        island[i][1] = y;
    }
    long double E;
    cin >> E;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            sorted.push_back({dist(i, j), i, j});
        }
    }
    sort(sorted.begin(), sorted.end());
    long long result = 0;
    for (auto i : sorted)
    {
        if (union_find.merge(i[1], i[2]))
        {
            result += i[0];
        }
    }
    cout << result * E << "\n";
}

int main(int argc, char **argv)
{
    int test_case;
    int T;

    freopen("re_sample_input.txt", "r", stdin);
    cin >> T;

    cout.precision(0);
    cout << fixed;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cout << "#" << test_case << " ";
        solve();
    }
    return 0;
}