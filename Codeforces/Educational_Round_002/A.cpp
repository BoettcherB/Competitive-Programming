#include <iostream>
#include <string>

bool is_integer(const std::string& str) {
    if (str.length() == 0)
        return false;
    if (str[0] == '0' && str.length() > 1)
        return false;
    for (char c : str) {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string str;
    std::cin >> str;
    std::string a, b;
    int start = 0, pos = 0;
    while (true) {
        if (pos == str.length() || str[pos] == ',' || str[pos] == ';') {
            if (is_integer(str.substr(start, pos - start)))
                a.append(str.substr(start, pos - start) + ",");
            else
                b.append(str.substr(start, pos - start) + ",");
            if (pos == str.length())
                break;
            start = pos + 1;
        }
        ++pos;
    }
    if (a.length() > 0) {
        a.erase(a.end() - 1);
        std::cout << '"' << a << '"' << '\n';
    } else {
        std::cout << "-\n";
    }
    if (b.length() > 0) {
        b.erase(b.end() - 1);
        std::cout << '"' << b << '"' << '\n';
    } else {
        std::cout << "-\n";
    }
}
