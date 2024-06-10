/*

You are given an array arr of n integers. Your task is to find the maximum sum
of any subarray that has a length between a and b inclusive.

Constraints
    1 <= n <= 200,000
    1 <= a <= b <= n
    -1,000,000,000 <= arr[i] <= 1,000,000,000

Example Input:
8 1 2
-1 3 -2 5 3 -5 2 2

Example Output:
8

Firstly, calculate the prefix sum of arr. Note that the sum of a subarray from
indexes i to j is equal to prefix[j] - prefix[i-1]. Now, consider a subarray
ending at index i. This subarray must start at an index between i-b and i-a.
We can add all prefix sums between i-b and i-a to a set. If x is the smallest
value in the set, the maximum subarray ending at index i will have the sum
prefix[i] - x. If we move on to the next index (i+1), we can shift the range of
prefixes that are in the set by erasing prefix[i-b] from the set and adding
prefix[i-a+1] to the set.

*/

#include <iostream>
#include <set>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n, a, b, prefix[N] = { 0 };
    std::cin >> n >> a >> b;
    for (int i = 1; i <= n; ++i) {
        std::cin >> prefix[i];
        prefix[i] += prefix[i - 1];
    }
    std::multiset<long long> s;
    long long res = -1e18;
    int l = 1 - b, r = 1 - a;
    for (int i = 1; i <= n; ++i) {
        if (r >= 0)
            s.insert(prefix[r]);
        if (l > 0)
            s.erase(s.find(prefix[l - 1]));
        if (!s.empty())
            res = std::max(res, prefix[i] - *s.begin());
        ++l;
        ++r;
    }
    std::cout << res << '\n';
}
