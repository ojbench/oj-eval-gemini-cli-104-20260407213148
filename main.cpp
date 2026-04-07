#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int grid[1005][1005];
int dist_start[1005][1005];
int dist_end[1005][1005];
pair<int, int> q[1000005];

void solve() {
    int n, m;
    while (cin >> n >> m) {
        int start_x = -1, start_y = -1;
        int end_x = -1, end_y = -1;
        vector<pair<int, int>> shops;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
                if (grid[i][j] == 2) {
                    start_x = i;
                    start_y = j;
                } else if (grid[i][j] == 3) {
                    end_x = i;
                    end_y = j;
                } else if (grid[i][j] == 4) {
                    shops.push_back({i, j});
                }
            }
        }

        auto bfs = [&](int sx, int sy, int dist[1005][1005]) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist[i][j] = INF;
                }
            }
            int head = 0, tail = 0;
            if (sx != -1 && sy != -1) {
                dist[sx][sy] = 0;
                q[tail++] = {sx, sy};
            }
            while (head < tail) {
                auto [x, y] = q[head++];

                for (int i = 0; i < 4; ++i) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != 1) {
                        if (dist[nx][ny] == INF) {
                            dist[nx][ny] = dist[x][y] + 1;
                            q[tail++] = {nx, ny};
                        }
                    }
                }
            }
        };

        bfs(start_x, start_y, dist_start);
        bfs(end_x, end_y, dist_end);

        int min_dist = INF;
        for (auto shop : shops) {
            int d1 = dist_start[shop.first][shop.second];
            int d2 = dist_end[shop.first][shop.second];
            if (d1 != INF && d2 != INF) {
                min_dist = min(min_dist, d1 + d2);
            }
        }

        if (min_dist == INF) {
            cout << 0 << "\n";
        } else {
            cout << min_dist << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}