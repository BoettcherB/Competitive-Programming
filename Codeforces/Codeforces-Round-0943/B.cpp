#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, m;
        std::string A, B;
        std::cin >> n >> m >> A >> B;
        int res = 0, pos = 0;
        for (int i = 0; i < n; ++i) {
            while (pos < m) {
                if (A[i] == B[pos++]) {
                    ++res;
                    break;
                }
            }
        }
        std::cout << res << std::endl;
    }
}
