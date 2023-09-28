#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string str;
    int m;
    std::cin >> str >> m;
    for (int i = 0; i < m; ++i) {
        long long a, b, k;
        std::cin >> a >> b >> k;
        k = b - a + 1 - k % (b - a + 1);
        auto start = str.begin() + a - 1;
        std::rotate(start, start + k, str.begin() + b);
    }
    std::cout << str << '\n';
}
