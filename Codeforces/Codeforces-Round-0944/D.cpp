#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        std::string str;
        std::cin >> str;
        int segments = 1;
        int n = (int) str.length();
        for (int i = 1; i < n; ++i) {
            segments += str[i] != str[i - 1];
        }
        if (segments == 1)
            std::cout << 1 << '\n';
        else if (segments == 2)
            std::cout << (str[0] == '0' ? 1 : 2) << '\n';
        else
            std::cout << segments - 1 << '\n';
    }
}
