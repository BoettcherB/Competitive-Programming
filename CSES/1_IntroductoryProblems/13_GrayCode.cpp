/*

CSES: Introductory Problems: Gray Code

You are given an integer n. Create a list of all the 2^n bit strings of length
n, but order them in such a way that any two successive strings differ by only
one bit.

Constraints:
    1 <= n <= 16

Example Input:
2

Example Output:
00
01
11
10

This problem can be solved with a greedy method. Starting at the number 0, for
every number of n bits, try flipping every bit in order. If we flip a bit but
have already seen the resulting number, un-flip the bit and try the next one.
Once we find a new number that we haven't seen yet, we can mark it as seen and
print it in binary.

*/

#include <iostream>

const int N = 66000;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, num = 0;
    std::cin >> n;
    bool seen[N] = { false };
    bool found = true;
    while (found) {
        for (int i = n - 1; i >= 0; --i) {
            std::cout << ((num >> i) & 1);
        }
        std::cout << '\n';
        seen[num] = true;
        found = false;
        for (int i = 0; i < n; ++i) {
            int new_num = num ^ (1 << i);
            if (!seen[new_num]) {
                found = true;
                num = new_num;
                break;
            }
        }
    }
}
