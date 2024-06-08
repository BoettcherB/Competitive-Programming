#include <iostream>
#include <string>
#include <cctype>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string str;
    std::cin >> str;
    int upper = 0, lower = 0;
    for (char c : str) {
        if (std::islower(c)) ++lower;
        if (std::isupper(c)) ++upper;
    }
    for (char& c : str) {
        c = (lower > upper ? std::tolower(c) : std::toupper(c));
    }
    std::cout << str << '\n';
}
