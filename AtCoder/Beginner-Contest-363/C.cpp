#include <iostream>
#include <algorithm>
#include <string>

bool has_k_pal(const std::string& str, int k) {
    int p1 = 0, p2 = k - 1;
    while (p2 < (int) str.size()) {
        bool ok = true;
        int c1 = p1, c2 = p2;
        while (c1 < c2) {
            if (str[c1++] != str[c2--]) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
        ++p1; ++p2;
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::string str;
    std::cin >> n >> k >> str;
    std::sort(str.begin(), str.end());
    int cnt = !has_k_pal(str, k);
    while (std::next_permutation(str.begin(), str.end())) {
        cnt += !has_k_pal(str, k);
    }
    std::cout << cnt << '\n';
}
