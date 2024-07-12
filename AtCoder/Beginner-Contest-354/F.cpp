/*

Problem Statement: https://atcoder.jp/contests/abc354/tasks/abc354_f

Let L be the length of the longest increasing subsequence of the given array
arr[]. For any element arr[i] to be in any LIS of arr, then we need the length
of the LIS ending at i plus the length of the LIS starting at i to be equal to
L + 1 (+1 because we count the element arr[i] twice).

Let dp[i] be the length of the LIS ending at position i. This can easily be
found in O(n^2) time with: dp[i] = max(dp[i], dp[j] + 1) if arr[j] < arr[i] for
all j < i. This can be improved to O(nlog(n)) time with a segment tree. We will
need to create another array t where t[arr[i]] = dp[i]. To find dp[i] for an
element arr[i] using a segment tree, we can query for the max element on the
range t[0, arr[i] - 1]. In other words, find the max length LIS that ends with
an element that is less than arr[i]. Then, update t[arr[i]] to be the result of
the query plus 1. Since arr[i] can be very large (10^9), we need to compress
the values of arr[i] to the range [0, n-1]. This can be done easily with a map.

One method to quickly find the length of the longest LIS starting at position i
for all 0 <= i < n is to reverse the array i and negate all numbers. Then, we
can run the same algorithm above to compute dp2[] for this new array. dp2[i] is
the length of the LIS starting at position n - 1 - i. For every index i, if
dp[i] + dp2[n - 1 - i] is equal to L + 1, then the element at index i is an a
LIS of arr.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class SegTree {
    int n;
    std::vector<int> tree;

    void update(int cur, int tl, int tr, int index, int val) {
        if (tl == tr)
            tree[cur] = val;
        else {
            int mid = (tl + tr) / 2;
            if (index <= mid)
                update(cur * 2, tl, mid, index, val);
            else
                update(cur * 2 + 1, mid + 1, tr, index, val);
            tree[cur] = std::max(tree[cur * 2], tree[cur * 2 + 1]);
        }
    }

    long long query(int cur, int tl, int tr, int ql, int qr) const {
        if (ql <= tl && tr <= qr)
            return tree[cur];
        if (tl > qr || tr < ql)
            return 0;
        int mid = (tl + tr) / 2;
        return std::max(query(cur * 2, tl, mid, ql, qr),
            query(cur * 2 + 1, mid + 1, tr, ql, qr));
    }

public:
    SegTree(int n) : n{ n } {
        tree = std::vector<int>(4 * n);
    }

    void update(int index, int val) {
        update(1, 0, n - 1, index, val);
    }

    long long query(int ql, int qr) const {
        if (ql > qr) return 0;
        return query(1, 0, n - 1, ql, qr);
    }
};

std::vector<int> getLIS(const std::vector<int>& arr, int n) {
    std::vector<int> nums = arr, dp(n);
    std::sort(nums.begin(), nums.end());
    std::map<int, int> compressed;
    for (int i = 0; i < n; ++i) {
        compressed[nums[i]] = i;
    }
    SegTree st(n + 1);
    for (int i = 0; i < n; ++i) {
        int prev = st.query(0, compressed[arr[i]] - 1) + 1;
        st.update(compressed[arr[i]], prev);
        dp[i] = prev;
    }
    return dp;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n;
        std::cin >> n;
        std::vector<int> a1(n), a2(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a1[i];
            a2[n - 1 - i] = -a1[i];
        }
        std::vector<int> r1 = getLIS(a1, n), r2 = getLIS(a2, n);
        int maxLen = *std::max_element(r1.begin(), r1.end());
        std::vector<int> indexes;
        for (int i = 0; i < n; ++i) {
            if (r1[i] + r2[n - 1 - i] == maxLen + 1) {
                indexes.push_back(i + 1);
            }
        }
        int m = (int) indexes.size();
        std::cout << m << '\n';
        for (int i = 0; i < m; ++i) {
            std::cout << indexes[i] << " \n"[i == m - 1];
        }
    }
}
