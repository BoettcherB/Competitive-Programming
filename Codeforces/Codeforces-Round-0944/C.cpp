#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        std::vector<int> left;
        int cur = a == 12 ? 1 : a + 1;
        while (cur != b) {
            left.push_back(cur);
            cur = cur == 12 ? 1 : cur + 1;
        }
        bool cross = false;
        for (int x : left) {
            if (x == c || x == d) {
                cross = !cross;
            }
        }
        std::cout << (cross ? "YES" : "NO") << '\n';
    }
}
