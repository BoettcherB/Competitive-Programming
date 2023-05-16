/*

If we create an infinite string consisting of all the positive integers in a
row in increasing order, find the digit in position k in this string. Answer
this for q queries.

Infinite String: 123456789101112131415161718192021222324252627282930...

Constraints:
 - 1 <= q <= 1000
 - 1 <= k <= 1,000,000,000,000,000,000

Example Input:
3
7
19
12

Example Output:
7
4
1

There are 9 numbers with 1 digit, 90 numbers with 2 digits, 900 numbers with 3
digits... In total these numbers contain 9 digits, 180 digits, 2700 digits...
We can use this information to find out the number that contains the k'th
digit, as well as which digit within that number is the k'th digit.

*/

#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int q;
    std::cin >> q;
    while (q--) {
        long long k, digits = 1, pow = 9;
        std::cin >> k;
        while (k > digits * pow) {
            k -= digits * pow;
            pow *= 10;
            ++digits;
        }
        --k;
        long long num = k / digits + pow / 9;
        long long dig = digits - k % digits;
        while (--dig) {
            num /= 10;
        }
        std::cout << num % 10 << '\n';
    }
}
