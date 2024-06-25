/*

Problem Statement: https://codeforces.com/contest/1985/problem/G

To solve this problem, start by determining which numbers satisfy the condition
k * d(n) == d(k * n). We can do this by implementing d(n) and trying all values
of n from 0 to some upper bound (say, 10000). If we do this, we will see that
for a number to satisfy the condition, all digits of the number must be <= 9/k.

Intuitively, if all digits are <= 9/k and we multiply n * k, none of the digits
will overflow into the next digit. Therefore, the sum of the digits of n * k is
equal to k times the sum of the digits of n.

Now, the problem is this: Let count(l, r, k) be the number of numbers between
10^l and 10^r where all digits are <= 9/k. This range contains all numbers that
have d digits where l < d <= r. We can solve this by finding the answer for all
numbers that have up to r digits, and then subtracting the numbers that have up
to l digits (ie. count(l, r, k) = count(0, r, k) - count(0, l, k)). To find the
number of numbers with <= d digits that satisfy d[i] <= 9/k, we simply need to
take the number of possible values per digit (which is 9/k+1) to the d'th power
(because we are choosing from 9/k+1 values d times). Therefore, count(0, r, k)
= (9/k+1)^r and count(0, l, k) = (9/k+1)^l. To find these values, we can use
binary exponentiation which can solve a^b % m in O(log(b)) time.

*/

#include <iostream>

const int MOD = 1e9 + 7;

long long binexp(long long a, long long b, long long m = MOD) {
    a %= m;
    long long res = 1;
    while (b) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        long long l, r, k;
        std::cin >> l >> r >> k;
        long long res = binexp(9 / k + 1, r) - binexp(9 / k + 1, l);
        std::cout << (res + MOD) % MOD << '\n';
    }
}
