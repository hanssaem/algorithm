#include <iostream>
#include <set>

using namespace std;

int parent[101];
set<int> s;

void init(int n)
{
    for (int i = 0; i <= n; i++)
    {
        parent[i] = i;
    }
}

int find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void unite(int a, int b)
{
    int rootA = find(a);
    int rootB = find(b);
    if (rootA != rootB)
    {
        parent[rootB] = rootA;
    }
}

bool isSameSet(int a, int b)
{
    return find(a) == find(b);
}

int main(int argc, char **argv)
{
    int test_case;
    int T;
    // freopen("input.txt", "r", stdin);
    cin >> T;
    int N, M;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> M;
        int a, b;
        init(N);
        s.clear();
        for (int i = 0; i < M; i++)
        {
            cin >> a >> b;
            unite(a, b);
        }
        for (int i = 1; i <= N; i++)
        {
            s.insert(find(i));
        }

        cout << "#" << test_case << " " << s.size() << "\n";
    }
    return 0;
}