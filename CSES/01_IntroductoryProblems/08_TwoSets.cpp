/*

Given an integer n, divide the integers 1..n into 2 sets of equal sum. If this
is possible, print "YES", then print the size of the first set and all its
elements, then the size of the second set and all its elements. If this is not
possible, print "NO".

This division is possible if the sum of the first n numbers is even. The sum of
the first n numbers is s = n(n+1)/2. If s is even then each set will require a
sum of s/2. We can use a greedy approach to divide the numbers. Let rem1 be the
total sum that set 1 still requires (its initial value is s/2). Loop through
the numbers from n to 1. If the current number i is <= rem1, add i to set 1 and
subtract i from rem1. If i > rem1, add i to set 2.

Constraints:
 - 1 <= n <= 1,000,000

Example Input:
7

Example Output:
YES
4
1 2 4 7
3
3 5 6

*/

#include <iostream>
#include <list>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n;
    std::cin >> n;
    if ((n * (n + 1) / 2) % 2) {
        std::cout << "NO" << '\n';
        return 0;
    }
    long long remaining = n * (n + 1) / 4;
    std::list<int> set1, set2;
    for (int i = n; i > 0; --i) {
        if (remaining >= i) {
            set1.push_back(i);
            remaining -= i;
        } else {
            set2.push_back(i);
        }
    }
    std::cout << "YES\n" << set1.size() << '\n';
    for (int x : set1) {
        std::cout << x << ' ';
    }
    std::cout << '\n' << set2.size() << '\n';
    for (int x : set2) {
        std::cout << x << ' ';
    } std::cout << '\n';
}
