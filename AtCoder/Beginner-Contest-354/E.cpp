/*

Problem Statement: https://atcoder.jp/contests/abc354/tasks/abc354_e

This problem can be solved using bit DP. Since n <= 18, we can encode a 'state'
of the game using a single integer x: If the i'th card is still on the table,
the i'th bit of x is 1, and if the i'th card is removed, the i'th bit of x is
0. The max value of x is 2^n - 1 (when all n bits are 1). Let dp[i] be true if
it is possible for the current player to win if they encounter the game state
i. For each state i, use a double-nested for loop to find each pair of bits a
and b such that a == b == 1 (the a'th and b'th cards are still on the table)
and either the fronts of the a'th and b'th cards are the same or the backs of
the a'th and b'th cards are the same. If we remove these cards, the integer
encoding the new game state can be calculated: j = i ^ (1 << a) ^ (1 << b). (we
are just setting the a'th and b'th bits to 0). If it is not possible for the
next player to win at state j, then it is possible for the current player to
win at state i. Therefore, if dp[j] = false, then dp[i] = true;

*/

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> cards(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cards[i].first >> cards[i].second;
    }
    std::vector<bool> dp(1 << n);
    for (int i = 0; i < 1 << n; ++i) {
        for (int bit1 = 0; bit1 < n - 1; ++bit1) {
            if (!(i & (1 << bit1)))
                continue;
            for (int bit2 = bit1 + 1; bit2 < n; ++bit2) {
                int f1 = cards[bit1].first, f2 = cards[bit2].first;
                int b1 = cards[bit1].second, b2 = cards[bit2].second;
                if (!(i & (1 << bit2)) || (f1 != f2 && b1 != b2))
                    continue;
                if (!dp[i ^ (1 << bit1) ^ (1 << bit2)]) {
                    dp[i] = true;
                    break;
                }
            }
        }
    }
    std::cout << (dp[(1 << n) - 1] ? "Takahashi" : "Aoki") << '\n';
}
