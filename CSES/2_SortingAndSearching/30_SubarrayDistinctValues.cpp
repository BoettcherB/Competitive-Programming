/*

You are given an array of n integers [a0, a1, ..., an]. Your task is to find
the number of subarrays that have at most k distinct values.

Constraints
    1 <= k <= n <= 200,000
    1 <= a <= 1,000,000,000

Example Input:
5 2
1 2 3 1 1

Example Output:
10

This problem can be solved with a 2-pointers method. We can use p1 and p2 to
indicate the ends of a subarray [p1, p2]. Also, keep a set s of the values
within that subarray. If the number of distinct values in the range [p1, p2]
(the size of s) is <= k, then increment p2 and add a[p2] to s. If the number of
distinct values in [p1, p2] is > k, then we know that there are exactly p2-p1-1
subarrays starting at p1 that have <= k distinct values, so we add that to our
answer. We then increment p1. If a[p1] was the only instance of that value in
the range [p1, p2], then remove a[p1] from s. (We can keep a map containing the
indices of each value to quickly check this). If we reach a point where p2 = n
and every remaining subarray has <= k distinct values, we can calculate the
number of remaining subarrays with (p2-p1) * (p2-p1+1) / 2;

*/

#include <iostream>
#include <map>
#include <list>
#include <set>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k, arr[N];
    std::cin >> n >> k;
    std::map<int, std::list<int>> indices;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        indices[arr[i]].push_back(i);
    }
    std::set<int> s;
    int p1 = 0, p2 = 0;
    long long res = 0;
    while (p2 <= n) {
        if ((int) s.size() <= k) {
            if (p2 == n) break;
            s.insert(arr[p2++]);
        } else {
            res += p2 - p1 - 1;
            indices[arr[p1]].pop_front();
            if (indices[arr[p1]].empty() || indices[arr[p1]].front() >= p2)
                s.erase(arr[p1]);
            ++p1;
        }
    }
    res += 1LL * (p2 - p1) * (p2 - p1 + 1) / 2;
    std::cout << res << '\n';
}
