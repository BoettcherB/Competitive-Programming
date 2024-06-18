#include <iostream>
#include <vector>
#include <algorithm>

const int N = 1e6 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<long long> A(n), count(N);
    for (int i = 0; i < n; ++i) {
        std::cin >> A[i];
        ++count[A[i]];
    }
    std::sort(A.begin(), A.end());
    std::vector<long long> prefix(N);
    prefix[0] = count[0];
    for (int i = 1; i < N; ++i) {
        prefix[i] = count[i] + prefix[i - 1];
    }
    long long res = 0;
    for (int x = 1; x < N; ++x) {
        for (int y = 1; x * y < N; ++y) {
            int l = x * y - 1;
            int r = std::min((y + 1) * x - 1, N - 1);
            res += (prefix[r] - prefix[l]) * y * count[x];
        }
        res -= count[x] * (count[x] + 1) / 2;
    }
    std::cout << res << '\n';
}
