#include <iostream>

int solve(int n1, int n2, int n3, int n4) {
    int x = (n1 % 2 * 1) ^ (n2 % 2 * 2) ^ (n3 % 2 * 3) ^ (n4 % 2 * 4);
    if (x >= 4) {
        x -= 4;
        --n4;
    }
    if (x == 1) {
        if (n1) {
            --n1;
        } else if (n2 && n3) {
            --n2; --n3;
        } else return 0;
    } else if (x == 2) {
        if (n2) {
            --n2;
        } else if (n1 && n3) {
            --n1; --n3;
        } else return 0;
    } else if (x == 3) {
        if (n3) {
            --n3;
        } else if (n1 && n2) {
            --n1; --n2;
        } else return 0;
    }
    return (n1 % 2 == 1) + n1 / 2 + n2 / 2 + n3 / 2 + n4 / 2;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n1, n2, n3, n4;
        std::cin >> n1 >> n2 >> n3 >> n4;
        std::cout << solve(n1, n2, n3, n4) << '\n';
    }
}
