#include <iostream>

long long sumN(long long n) {
    return n * (n + 1) / 2;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        long long n, a, b;
        std::cin >> n >> a >> b;
        long long k = b <= a ? 0 : std::min(b - a, n);
        std::cout << sumN(b) - sumN(b - k) + (n - k) * a << '\n';
    }
}
