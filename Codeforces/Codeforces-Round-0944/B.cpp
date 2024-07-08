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
        bool found = false;
        for (int i = 1; i < (int) str.length(); ++i) {
            if (str[i] != str[0]) {
                std::swap(str[i], str[0]);
                found = true;
                break;
            }
        }
        if (found)
            std::cout << "YES" << '\n' << str << '\n';
        else
            std::cout << "NO" << '\n';
    }
}
