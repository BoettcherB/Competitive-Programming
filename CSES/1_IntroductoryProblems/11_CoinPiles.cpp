/*

CSES: Introductory Problems: Coin Piles

You have 2 coin piles containing a and b coins. On one move you can take 2
coins off of one pile and 1 coin off of the other. Is it possible to empty
both piles? Answer this for T test cases.

Constraints:
    1 <= T <= 100,000
    1 <= a, b <= 1,000,000,000

Example Input:
3
2 1
2 2
3 3

Example Output:
YES
NO
YES

If both piles have the same number of coins (a == b), then it is only possible
to make both piles empty if a and b are divisible by 3. If we take 2 from a and
1 from b, then 2 from b and 1 from a, a and b will be equal again and we will
have taken away 3 from both piles. If a != b, we can make them equal by
continually taking 2 from the larger pile and 1 from the smaller until they are
equal. The number of coins in each pile after making the piles equal, eq, needs
to be divisible by 3 and >= 0.

*/

#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int a, b;
        std::cin >> a >> b;
        int eq = std::min(a, b) - (std::max(a, b) - std::min(a, b));
        std::cout << (eq >= 0 && eq % 3 == 0 ? "YES\n" : "NO\n");
    }
}
