/*

CSES: Introductory Problems: Two Sets

Given an integer n, divide the integers 1..n into 2 sets of equal sum. If this
is possible, print "YES", then print the size of the first set and all its
elements, then the size of the second set and all its elements. If this is not
possible, print "NO".

Constraints:
    1 <= n <= 1,000,000

Example Input:
7

Example Output:
YES
4
1 2 4 7
3
3 5 6

This division is possible if the sum of the first n numbers is even. The sum of
the first n numbers is s = n(n+1)/2. If s is even then each set will require a
sum of s/2. We can use a greedy approach to divide the numbers. Let sum1 be the
total sum that set 1 currently has. Loop through the numbers from n to 1. If
adding the current number i to set 1 will cause sum1 to be greater than s/2, 
add i to set 2. Otherwise add i to set 1.

*/

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n;
    std::cin >> n;
    long long total = n * (n + 1) / 2;
    if (total % 2 == 1) {
        std::cout << "NO\n";
        return 0;
    }
    std::vector<int> s1, s2;
    long long sum1 = 0;
    for (int i = n; i > 0; --i) {
        if (sum1 + i <= total / 2) {
            sum1 += i;
            s1.push_back(i);
        } else {
            s2.push_back(i);
        }
    }
    std::cout << "YES\n";
    std::cout << s1.size() << '\n';
    for (int x : s1) {
        std::cout << x << ' ';
    }
    std::cout << '\n' << s2.size() << '\n';
    for (int x : s2) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}
