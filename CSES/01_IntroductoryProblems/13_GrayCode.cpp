/*

You are given an integer n. Create a list of all the 2^n bit strings of length
n, but order them in such a way that any two successive strings differ by only
one bit.

This problem can be solved with a greedy method. For every bit string, we can
try flipping every bit in order. If we flip a bit but have already seen the
resulting string, un-flip the bit and try the next one. Once we find a new bit
string that we haven't seen yet, we can mark it as seen and print it. One
optimization is to treat each bit string as a number, since comparing numbers
is faster than comparing strings.

Constraints:
 - 1 <= n <= 16

Example Input:
2

Example Output:
00
01
11
10

*/

#include <iostream>
#include <string>
#include <cmath>

const int N = 7e4 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::string str(n, '0');
    int str_val = 0;
    bool seen[N] = { true };
    bool change = true;
    std::cout << str << '\n';
    while (change) {
        change = false;
        for (int i = n - 1; i >= 0; --i) {
            int p2i = (int) std::exp2(i);
            int new_val = str_val + (str[i] == '0' ? p2i : -p2i);
            if (!seen[new_val]) {
                str[i] = str[i] == '0' ? '1' : '0';
                std::cout << str << '\n';
                str_val = new_val;
                seen[str_val] = change = true;
                break;
            }
        }
    }
}
