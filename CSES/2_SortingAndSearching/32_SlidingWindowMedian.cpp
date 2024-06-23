/*

CSES: Sorting and Searching: Sliding Window Median

You are given an array of n integers [a0, a1, ..., an] and an integer k. Your
task is to find the median value for each window of length k ([0, k-1], [1, k],
[2, k+1], ..., [n-k, n-1]). Print each of the n-k+1 medians. If k is even and
there are 2 medians per window, print the smaller value.

Constraints:
    1 <= k <= n <= 200,000
    1 <= a <= 1,000,000,000

Example Input:
8 3
2 4 3 5 8 1 2 1

Example Output:
3 4 5 5 2 1

For this problem, we can keep 2 multisets, one named 'low' which stores the k/2
lowest values in the window, and one named 'high' which stores the k/2 highest
values in the window. If k is odd, low should store k/2+1 values. This way, the
median value is always the last value in low (regardless of whether k is even
or odd). Lets say we start on the first window [0, k-1]. We first fill the low
and high sets with the first k values in a[n]. Then we print the median (the
last value in low) and move on the next window [1, k]. To do this we need to
remove a[0] from the sets and add a[k] to the sets. When the values are added
to the correct set and the sets are rebalanced such that high always has k/2
elements and low has either k/2 or k/2+1 elements (depending on the parity of
k), then we can print the median and move on to the next window. Do this for
all windows.

*/

#include <iostream>
#include <set>

const int N = 2e5 + 10;
int n, k, arr[N];
std::multiset<int> low, high;

void insert(int x) {
    high.insert(x);
    if ((int) high.size() > k / 2) {
        low.insert(*high.begin());
        high.erase(high.begin());
    }
}

void remove(int x) {
    if (high.size() > 0 && *high.begin() <= x) {
        high.erase(high.find(x));
        high.insert(*(--low.end()));
        low.erase(--low.end());
    } else {
        low.erase(low.find(x));
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        if (i < k)
            insert(arr[i]);
    }
    std::cout << *(--low.end());
    for (int i = 0; i < n - k; ++i) {
        remove(arr[i]);
        insert(arr[i + k]);
        std::cout << ' ' << *(--low.end());
    }
    std::cout << '\n';
}
