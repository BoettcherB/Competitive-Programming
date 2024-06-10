#include <iostream>
#include <algorithm>
#include <vector>

const int N = 2e5 + 10;
int to[N], dist[N], component[N];
bool visited[N];

void dfs(int start, int& comp) {
    std::vector<int> nodes;
    int cur = start;
    while (!visited[cur]) {
        visited[cur] = true;
        nodes.push_back(cur);
        cur = to[cur];
    }
    int n = (int) nodes.size();
    int pos = n;
    if (dist[cur] == -1) {
        ++comp;
        pos = std::find(nodes.begin(), nodes.end(), cur) - nodes.begin();
        for (int i = pos; i < n; ++i) {
            dist[nodes[i]] = 0;
            component[nodes[i]] = comp;
        }
    }
    for (int i = pos - 1; i >= 0; --i) {
        dist[nodes[i]] = 1 + dist[to[nodes[i]]];
        component[nodes[i]] = component[to[nodes[i]]];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> to[i];
    }
    std::fill(dist, dist + n + 1, -1);
    int comp = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i])
            dfs(i, comp);
    }
    std::vector<std::vector<int>> comps(comp + 1);
    std::vector<int> onCycle(comp + 1);
    for (int i = 1; i <= n; ++i) {
        comps[component[i]].push_back(i);
        onCycle[component[i]] += (dist[i] == 0);
    }
    long long res = 0;
    for (int i = 1; i <= comp; ++i) {
        for (int j = 0; j < (int) comps[i].size(); ++j) {
            res += dist[comps[i][j]] + onCycle[i];
        }
    }
    std::cout << res << '\n';
}
