/*

CSES: Sorting and Searching: Reading Books

There are n books and each book has a time t that it takes someone to read. Two
people want to fully read each book. They cannot read the same book at the same
time. What is the minimum amount of time needed for both people to read all the
books?

Constraints:
    1 <= n <= 200,000
    1 <= t <= 1,000,000,000

Example Input:
3
2 8 3

Example Output:
16

The minimum total time it takes to read all the books is just the sum of their
reading times. However, if there is a book b whose reading time is greater than
half the total sum of all reading times, then more time is needed (2 times the 
reading time of book b).

*/

#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, a, max = 0;
    long long sum = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a;
        max = std::max(max, a);
        sum += a;
    }
    std::cout << std::max(sum, 2LL * max) << '\n';
}
