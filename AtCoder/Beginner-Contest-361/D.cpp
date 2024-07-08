#include <iostream>
#include <string>
#include <set>
#include <queue>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::string A, B;
    std::cin >> n >> A >> B;
    A += "--";
    B += "--";
    std::set<std::string> seen;
    std::queue<std::pair<std::string, int>> q;
    q.emplace(A, 0);
    while (!q.empty()) {
        std::string cur = q.front().first;
        int moves = q.front().second;
        q.pop();
        if (seen.find(cur) != seen.end())
            continue;
        seen.emplace(cur);
        if (cur == B) {
            std::cout << moves << '\n';
            return 0;
        }
        int emptyspace = (int) cur.find('-');
        for (int i = 0; i < n + 1; ++i) {
            if (std::abs(emptyspace - i) <= 1)
                continue;
            std::swap(cur[i], cur[emptyspace]);
            std::swap(cur[i + 1], cur[emptyspace + 1]);
            q.emplace(cur, moves + 1);
            std::swap(cur[i], cur[emptyspace]);
            std::swap(cur[i + 1], cur[emptyspace + 1]);
        }
    }
    std::cout << -1 << '\n';
}
