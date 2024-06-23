#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        std::string a, b;
        std::cin >> a >> b;
        std::swap(a[0], b[0]);
        std::cout << a << ' ' << b << '\n';
    }
}
