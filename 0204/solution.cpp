#include <iostream>
using namespace std;

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

#include <vector>
#include <set>
#include <queue>
#include <string>
#include <cstring>

// The below commented functions are for your reference. If you want
// to use it, uncomment these functions.
/*
int mstrcmp(const char *a, const char *b)
{
    int i;
    for (i = 0; a[i] != '\0'; i++)
    {
        if (a[i] != b[i])
            return a[i] - b[i];
    }
    return a[i] - b[i];
}

int mstrncmp(const char *a, const char *b, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (a[i] != b[i])
            return a[i] - b[i];
    }
    return 0;
}

int mstrlen(const char *a)
{
    int len = 0;

    while (a[len] != '\0')
        len++;

    return len;
}

void mstrcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}

void mstrncpy(char *dest, const char *src, int len)
{
    for (int i = 0; i<len; i++)
    {
        dest[i] = src[i];
    }
    dest[len] = '\0';
}
*/

int parent[50001], cnt[50001];

vector<set<int>> child;
vector<string> dir_name;
queue<int> que;

int get_index()
{
    int idx = que.front();
    que.pop();
    return idx;
}

void update_cnt(int idx, int n)
{
    cnt[idx] += n;
    if (parent[idx] >= 0)
    {
        update_cnt(parent[idx], n);
    }
}

void node_insert(int parent_n, int child_n)
{
    child[parent_n].insert(child_n);
    parent[child_n] = parent_n;
    update_cnt(parent_n, cnt[child_n]);
}

void unlink(int idx)
{
    if (parent[idx] >= 0)
    {
        update_cnt(parent[idx], -cnt[idx]);
        child[parent[idx]].erase(idx);
    }
    parent[idx] = -1;
}

int copy_node(int src, int dst)
{
    int new_idx = get_index();
    cnt[new_idx] = cnt[src];
    dir_name[new_idx] = dir_name[src];
    for (int i : child[src])
    {
        int tmp = copy_node(i, new_idx);
        child[new_idx].insert(tmp);
    }
    parent[new_idx] = dst;
    return new_idx;
}

void del_node(int idx)
{
    for (auto i : child[idx])
    {
        del_node(i);
    }
    child[idx].clear();
    que.push(idx);
    parent[idx] = -1;
    cnt[idx] = 0;
}

int get_path_idx(char path[PATH_MAXLEN + 1])
{
    int ret = 0;
    char *ptr = strtok(path, "/");
    while (ptr != NULL)
    {
        for (auto i : child[ret])
        {
            if (dir_name[i] == ptr)
            {
                ret = i;
                break;
            }
        }
        ptr = strtok(NULL, "/");
    }
    return ret;
}

void init(int n)
{
    while (!que.empty())
    {
        que.pop();
    }
    memset(cnt, 0, sizeof(cnt));
    memset(parent, -1, sizeof(parent));
    child.clear();
    dir_name.clear();
    child.resize(n + 1);
    dir_name.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        que.push(i);
    }
    cnt[0] = 1;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1])
{
    int t = get_path_idx(path);
    int new_idx = get_index();
    cnt[new_idx] = 1;
    dir_name[new_idx] = name;
    node_insert(t, new_idx);
}

void cmd_rm(char path[PATH_MAXLEN + 1])
{
    int t_idx = get_path_idx(path);
    unlink(t_idx);
    del_node(t_idx);
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1])
{
    int src_idx = get_path_idx(srcPath);
    int dst_idx = get_path_idx(dstPath);
    int get_idx = copy_node(src_idx, dst_idx);
    update_cnt(dst_idx, cnt[get_idx]);
    child[dst_idx].insert(get_idx);
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1])
{
    int src_idx = get_path_idx(srcPath);
    unlink(src_idx);
    node_insert(get_path_idx(dstPath), src_idx);
}

int cmd_find(char path[PATH_MAXLEN + 1])
{
    return cnt[get_path_idx(path)] - 1;
}