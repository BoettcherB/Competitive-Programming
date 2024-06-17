/*

Count the number of numbers between a and b (inclusive) where no 2 consecutive
digits are the same

Constraints
0 <= a <= b <= 1,000,000,000,000,000,000

Example Input:
123 321

Example Output:
171

Lets call a number 'good' if it has no 2 consecutive digits that are the same. 
The answer for the range [a, b] is the same as [0, b] - [0, a-1]. Therefore, we
can define a simpler problem count(n) where we just need to find the number of
'good' numbers that are <= n, and then solve this problem for b and a-1.

Assume n has k digits. One way to find count(n) is to split up the work by
finding the 'good' numbers that have k-1 digits, and then finding the 'good'
numbers that have k digits but are <= n. When finding all 'good' numbers with
k-1 digits, we do not have to worry about an upper bound, so the dp is very
simple. Let dp[i][j] be the number of 'good' numbers with i digits that end in
digit j. Initially, dp[1][j] = 1 for all j. Then, dp[i][j] is the number of
'good' numbers with i-1 digits that do not end in j: SUM(dp[i-1][x] for all 0
<= x <= 9) minus dp[i-1][j]. To find the number of 'good' numbers with k digits
we use a similar algorithm but we must take into account the digits of n so
that we do not count any numbers that are > n. For this we will have 2 arrays:
below[i][j] is the number of 'good' numbers that have i digits, that end in
j, and that are < the first i digits of n. same[i][j] is 1 if there is a good
number that is the same as the first i digits of n. For example if n is 827,
then same[1][8] = same[2][2] = same[3][7] = 1. However, if n = 887, then
same[1][8] = 1 but same[2][8] = same[3][7] = 0. Initially, below[1][x] = 1 for
all 1 <= x < the first digit of n. If j < the i'th digit of n, then below[i][j]
= SUM(below[i-1][x] + same[i-1][x] for all 0 <= x <= 9) - below[i-1][j] -
same[i-1][j]. If j >= the i'th digit of n, then below[i][j] = SUM(below[i-1][x]
for all 1 <= x <= 9) - below[i-1][j]. Once count(n) is complete, we can find
the number of 'good' numbers between a and b by count(b) - count(a-1).

*/

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

long long sum(const std::vector<long long>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 0LL);
}

long long prevDigits(long long num) {
    int digits = std::to_string(num).length();
    if (digits == 1)
        return num != 0;
    std::vector<long long> dp = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    long long total = 10;
    for (int i = 2; i < digits; ++i) {
        std::vector<long long> dp2(10);
        dp2[0] = 1;
        for (int j = 0; j < 10; ++j) {
            dp2[j] += total - dp[j];
        }
        total = sum(dp2);
        dp = dp2;
    }
    return total;
}

long long curDigits(long long num) {
    std::string str = std::to_string(num);
    std::vector<long long> below(10), same(10);
    for (int i = 1; i < str[0] - '0'; ++i) {
        below[i] = 1;
    }
    same[str[0] - '0'] = 1;
    for (int i = 2; i <= (int) str.length(); ++i) {
        std::vector<long long> below2(10), same2(10);
        int d = str[i - 1] - '0';
        long long sumBelow = sum(below), sumSame = sum(same);
        for (int j = 0; j < 10; ++j) {
            if (j < d)
                below2[j] = sumSame + sumBelow - below[j] - same[j];
            else if (j > d)
                below2[j] = sumBelow - below[j];
            else {
                below2[j] = sumBelow - below[j];
                same2[j] = sumSame - same[j];
            }
        }
        below = below2;
        same = same2;
    }
    return sum(below) + sum(same);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long a, b;
    std::cin >> a >> b;
    long long resA = prevDigits(a - 1) + curDigits(a - 1);
    long long resB = prevDigits(b) + curDigits(b);
    std::cout << (a == 0 ? resB : resB - resA) << '\n';
}
