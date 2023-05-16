/*

You have 2 coin piles containing a and b coins. On one move you can take 2
coins off of one pile and 1 coin off of the other. Is it possible to empty
both piles? Answer this for T test cases.

Constraints:
 - 1 <= T <= 100,000
 - 1 <= a, b <= 1,000,000,000

Example Input:
3
2 1
2 2
3 3

Output:
YES
NO
YES

If both piles have the same number of coins (a == b), then it is only possible
to make both piles empty if a and b are divisible by 3. If we take 2 from a and
1 from b, then 2 from b and 1 from a, a and b will be equal again and we will
have taken away 3 from both piles. If a != b, we can make them equal by
continually taking 2 from the larger pile and 1 from the smaller until they are
equal. However, this is only possible if the larger is less than twice the
smaller.

*/

#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        long long a, b;
        std::cin >> a >> b;
        if (a > b)
            std::swap(a, b);
        if (2 * a < b || (a - (b - a)) % 3)
            std::cout << "NO" << '\n';
        else
            std::cout << "YES" << '\n';
    }
}
