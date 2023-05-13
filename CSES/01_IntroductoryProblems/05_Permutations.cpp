/*

Given an integer n, construct a permutation of the numbers 1..n where no two
adjacent elements have a different of 1. If no such permutation exists, print
"NO SOLUTION". If there are multiple possible solutions, print any of them.

The only values of n where no solution exists are 2 and 3. For every other
value of n we can print all the even numbers, then all the odd numbers.

Constraints:
 - 1 <= n <= 1,000,000

Example Input:
5

Example Output:
4 2 5 3 1

*/

#include <iostream>

const int N = 1e6 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    if (n == 2 || n == 3) {
        std::cout << "NO SOLUTION";
    } else {
        for (int i = 2; i <= n; i += 2) {
            std::cout << i << ' ';
        }
        for (int i = 1; i <= n; i += 2) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';
}
