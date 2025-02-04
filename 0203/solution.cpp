#include <vector>
using namespace std;

int h, w, c_c, c_r;
vector<char> memo[301];
int c_list[301][26];

void init(int H, int W, char mStr[])
{
    h = H;
    w = W;
    c_c = 0;
    c_r = 0;
    memset(c_list, 0, sizeof(c_list));
    int i = 0;
    for (int i = 0; i < 301; i++)
    {
        memo[i].clear();
    }
    while (mStr[i] != '\0')
    {
        memo[i / w].push_back(mStr[i]);
        c_list[i / w][mStr[i] - 'a']++;
        i++;
    }
}

void insert(char mChar)
{
    memo[c_r].insert(memo[c_r].begin() + c_c, mChar);
    c_list[c_r][mChar - 'a']++;
    char carry = '\0';
    for (int i = c_r; i < h; i++)
    {
        if (memo[i].size() > w)
        {
            carry = memo[i].back();
            memo[i].pop_back();
            c_list[i][carry - 'a']--;

            if (i + 1 < h)
            {
                memo[i + 1].insert(memo[i + 1].begin(), carry);
                c_list[i + 1][carry - 'a']++;
            }
        }
        else
        {
            break;
        }
    }
    c_c++;
    if (c_c >= w)
    {
        c_r++;
        c_c = 0;
    }
}

char moveCursor(int mRow, int mCol)
{
    c_r = mRow - 1;
    c_c = mCol - 1;
    // 문자 길이보다 더 크다면 끝으로 옮김
    if (memo[c_r].size() <= c_c)
    {
        while (memo[c_r].empty())
        {
            c_r--;
        }
        c_c = memo[c_r].size();
        return '$';
    }
    return memo[c_r][c_c];
}

int countCharacter(char mChar)
{
    int cnt = 0;
    // 해당 줄
    for (int i = c_c; i < memo[c_r].size(); i++)
    {
        cnt += memo[c_r][i] == mChar;
    }
    // 다음줄부터는 문자리스트에서 알아냄
    for (int i = c_r + 1; i < h; i++)
    {
        cnt += c_list[i][mChar - 'a'];
    }

    return cnt;
}
