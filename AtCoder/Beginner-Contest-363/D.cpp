#include <iostream>
#include <vector>
#include <string>

const int N = 40;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<long long> pals(N);
    pals[1] = 10; pals[2] = 9;
    for (int digits = 3; digits < N - 1; digits += 2) {
        pals[digits] = pals[digits - 1] * 10;
        pals[digits + 1] = pals[digits];
    }
    
    long long n;
    std::cin >> n;
    int digits = 0;
    for (int i = 1; i < N; ++i) {
        if (n <= pals[i]) {
            digits = i;
            break;
        }
        n -= pals[i];
    }
    n -= 1;
    int ind = digits / 2 - (digits % 2 == 0);
    std::string str(digits, '0');
    while (n > 0) {
        str[ind] = str[digits - ind - 1] = char(n % 10 + '0');
        --ind;
        n /= 10;
    }
    if (digits != 1) {
        ++str[0];
        ++str[str.length() - 1];
    }
    std::cout << str << '\n';
}
