/*

You are given an array containing n integers [a0, a1, ..., an]. Your task is to
find the length of the longest increasing subsequence. A subsequence is a
sequence that can be derived from the array by deleting some elements without
changing the order of the remaining elements.

Constraints:
    1 <= n <= 2,000,000
    1 <= a <= 1,000,000,000

Example Input:
8
7 3 5 3 6 2 9 8

Example Output:
4

This problem can be solved with a single vector v. This vector does not store
the subsequence itself. Instead, the value at v[i] means the best subsequence
of length i + 1 ends in v[i]. (A subsequence is best if it ends in the smallest
value. A subsequence that ends in 4 is better than one that ends in 10 because
the one that ends in 4 could be increased by values 5-10 while the other can't
be). The number of elements in v is the length of the longest subsequence. Loop
through all the values in a[n]. For every a[i], use a binary search function to
find the first value v[j] that is >= a[i]. If there is none, and v currently
has k elements, then this value is > the end of the best subsequnce of length k
and can extend it by 1. So push the value to the back of the vector. If we find
a value v[j] that is >= a[i], we can replace v[j] with a[i]. This means that
the best subsequence of length j+1 now ends with the value a[i].

Example:
arr: 2 6 8 3 1 5 7
v after every step:
1: 2
2: 2 6
3: 2 6 8
4: 2 3 8   The longest subsequence is still length 3 but in the first 4 values
           of arr, the best length 2 subsequence now ends in 3 instead of 6.
5: 1 3 8   The best length 1 subsequence from the first 5 values now ends in 1.
6: 1 3 5   The best length 3 subsequence from the first 6 values now ends in 5.
7: 1 3 5 7 The best length 4 subsequence ends in 7.
The length of v is 4 so the longest subsequence is length 4.

*/

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, a;
    std::cin >> n;
    std::vector<int> dp;
    for (int i = 0; i < n; ++i) {
        std::cin >> a;
        auto itr = std::lower_bound(dp.begin(), dp.end(), a);
        if (itr == dp.end())
            dp.push_back(a);
        else
            dp[itr - dp.begin()] = a;
        for (int i = 0; i < (int) dp.size(); ++i) {
            std::cout << dp[i] << " \n"[i == (int) dp.size() - 1];
        }
    }
    std::cout << dp.size() << '\n';
}
