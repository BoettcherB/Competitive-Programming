#include <iostream>
#include <cmath>

const int N = 5e6 + 10;
long long factorCount[N], prefix[N];

int find_first_factor(int n) {
    if (n % 2 == 0) return 2;
    int s = std::sqrt(n);
    for (int i = 3; i <= s; i += 2) {
        if (n % i == 0)
            return i;
    }
    return n;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    factorCount[1] = prefix[1] = 0;
    for (int i = 2; i < N; ++i) {
        factorCount[i] = factorCount[i / find_first_factor(i)] + 1;
        prefix[i] = prefix[i - 1] + factorCount[i];
    }

    int tc = 1;
    std::cin >> tc;
    while (tc--) {
        int a, b;
        std::cin >> a >> b;
        std::cout << prefix[a] - prefix[b] << '\n';
    }
}
