#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

using namespace std;

int tc, n;
int map[20][20];
int max_answer;

int dy[4] = { 1, 1, -1,-1 };
int dx[4] = { 1, -1, -1, 1 };
int number_visited[101];

struct Point
{
    int y;
    int x;
};


void init()
{
    max_answer = 0;
    memset(number_visited, 0, sizeof(number_visited));
}

void print(Point cp)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (cp.y == i && cp.x == j)
                cout << '@' << ' ';
            else
                cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}


void solve(Point start, Point now, int sum, int di)
{
    if (di == 3 && start.x == now.x && start.y == now.y)
    {
        if (sum > max_answer) {
            max_answer = sum;
            //cout << "FOUND MAX: " <<max << '\n';
            return;
        }
    }

    Point next;
    for (int i = 0; i < 2; i++) //직진, 우회전
    {
        if (sum == 0 && i == 1) continue;
        if (di + i == 4) return;
        next.y = now.y + dy[di + i];
        next.x = now.x + dx[di + i];

        if (next.y < 0 || next.y >= n || next.x < 0 || next.x >= n) continue;
        if (number_visited[map[next.y][next.x]]) continue;

        number_visited[map[next.y][next.x]] = 1;

        solve(start, next, sum + 1, di + i);

        number_visited[map[next.y][next.x]] = 0;

    }
}

int main()
{
    freopen("sample_input.txt", "r", stdin);

    cin >> tc;

    for (int t = 1; t <= tc; t++)
    {
        init();
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {

                cin >> map[i][j];
            }
        }


        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                solve({ i,j }, { i,j }, 0, 0);
            }
        }

        cout << '#' << t << ' ';
        if (max_answer == 0) cout << -1;
        else cout << max_answer;
        cout << '\n';
    }

}

/*

1
4
9 8 9 8
4 6 9 4
8 7 7 8
4 5 3 5



1
8 2 9 6 6
1 9 3 3 4
8 2 3 3 6
4 3 4 4 9
7 4 6 3 5
*/