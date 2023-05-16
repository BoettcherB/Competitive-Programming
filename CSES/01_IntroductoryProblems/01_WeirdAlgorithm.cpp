/*

You are given a single integer n. Perform the following operation on n until
n is equal to 1:
 - If n is even, n = n / 2
 - If n is odd, n = 3n + 1
Print every value of n until n is equal to 1.

Constraints:
 - 1 <= n <= 1,000,000

Example Input:
3

Example Output:
3 10 5 16 8 4 2 1

The only thing to watch out for in this problem is that n could become very
large and needs to be stored in a 64 bit number.

*/

#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n;
    std::cin >> n;
    while (n != 1) {
        std::cout << n << ' ';
        n = (n % 2) ? 3 * n + 1 : n / 2;
    }
    std::cout << n << '\n';
}
