#include <iostream>
#include <vector>
#include <string>
#include <set>

std::string solve() {
    int n, c, d;
    std::cin >> n >> c >> d;
    std::multiset<int> s;
    for (int i = 0; i < n * n; ++i) {
        int x;
        std::cin >> x;
        s.insert(x);
    }
    std::vector<std::vector<int>> mat(n, std::vector<int>(n));
    mat[0][0] = *s.begin();
    s.erase(s.begin());
    for (int i = 1; i < n; ++i) {
        auto itr = s.find(mat[i - 1][0] + c);
        if (itr == s.end()) return "NO";
        mat[i][0] = *itr;
        s.erase(itr);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            auto itr = s.find(mat[i][j - 1] + d);
            if (itr == s.end()) return "NO";
            mat[i][j] = *itr;
            s.erase(itr);
        }
    }
    return "YES";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        std::cout << solve() << '\n';
    }
}
