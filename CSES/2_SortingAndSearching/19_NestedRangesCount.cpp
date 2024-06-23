/*

CSES: Sorting and Searching: Nested Ranges Count

You are given n ranges [a, b]. Your task is to find out, for each range, how
many other ranges it contains and how many other ranges contain it. Output a
line that describes for each range (in the input order) how many other ranges
it contains, Then another line that describes for each range how many other
ranges contain it.

Constraints:
    1 <= n <= 200,000
    1 <= a, b <= 1,000,000,000
    Each range appears only once

Example Input:
4
1 6
2 4
4 8
3 6

Example Output:
2 0 0 0
0 1 0 1

To solve, sort the ranges by 'a', then by 'b' in reverse. Next, split each
range up into endpoints (while keeping track of whether the endpoint opens or
closes the range) and sort the 2n endpoints. Loop through each endpoint. When
an opening endpoint is found, mark the range as open. When a closing endpoint
is found for range i, we can determine how many other ranges contain range i
based on how many other ranges are open. Out of all ranges, we can count how
many ranges are both open and start before range i's start. We can do a similar
operation to find out how many ranges are contained in a range. Loop through 
each endpoint again. When a closing enpoint is found for range i, mark the
range as closed. Then, count how many ranges are closed that have a starting
value that is >= range i's start.

A segment tree is a good data structure for this problem since we are doing
updates and queries on an array. In this case, the array (arr) is the n ranges.
arr[i] is either 1 or 0. In the first part of the problem (determining how many
ranges contain each range), we can set arr[i] = 1 to mean that the i'th range
is open. We do this whenever we encounter the starting endpoint of range i.
When we encounter the closing endpoint of range i, we can mark it as closed
(arr[i] = 0) and then do a query to find out how many ranges contain range i.
Since the ranges are sorted by their starting index, we know that each range
with an index < i has a smaller starting index, so any range with index [0,i-1]
that is open will contain range i. A segment tree query for the sum of the
array from [0,i-1] will be the answer. For the second part of the problem
(determining how many ranges are contained in each range), arr[i] = 1 means
that range i has been closed. When we encounter the closing enpoint of a range
i, we can set arr[i] = 1. Any ranges that have an index > i that have already
been closed will be contained in range i. We can query for the sum of [i+1,n]
for the anser.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

struct Range {
    int l, r, index;
    bool operator<(const Range& other) const {
        return l == other.l ? r > other.r : l < other.l;
    }
};

struct Endpoint {
    int p, type, index;
    bool operator<(const Endpoint& other) const {
        if (p == other.p)
            return type == other.type ? index > other.index : type;
        return p < other.p;
    }
};

class SegmentTree {
    int n, tree[4 * N] = { 0 };

    void update(int cur, int tl, int tr, int index, int val) {
        if (tl == tr)
            tree[cur] = val;
        else {
            int mid = (tl + tr) / 2;
            if (index <= mid)
                update(cur * 2, tl, mid, index, val);
            else
                update(cur * 2 + 1, mid + 1, tr, index, val);
            tree[cur] = tree[cur * 2] + tree[cur * 2 + 1];
        }
    }

    int query(int cur, int tl, int tr, int ql, int qr) {
        if (ql <= tl && tr <= qr)
            return tree[cur];
        if (ql > tr || qr < tl)
            return 0;
        int mid = (tl + tr) / 2;
        return query(cur * 2, tl, mid, ql, qr)
            + query(cur * 2 + 1, mid + 1, tr, ql, qr);
    }

public:
    SegmentTree(int n) : n{ n } {}

    void update(int index, int val) {
        update(1, 0, n - 1, index, val);
    }

    int query(int l, int r) {
        if (r < l || l > r) return 0;
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n;
    std::cin >> n;
    Range ranges[N];
    for (int i = 0; i < n; ++i) {
        std::cin >> ranges[i].l >> ranges[i].r;
        ranges[i].index = i;
    }
    std::sort(ranges, ranges + n);
    Endpoint pts[2 * N];
    for (int i = 0; i < n; ++i) {
        pts[i] = { ranges[i].l, 0, i };
        pts[i + n] = { ranges[i].r, 1, i };
    }
    std::sort(pts, pts + 2 * n);
    int contains[N], containedBy[N];
    SegmentTree st(n);
    for (int i = 0; i < 2 * n; ++i) {
        int ind = pts[i].index;
        if (pts[i].type == 0)
            st.update(ind, 1);
        else {
            containedBy[ranges[ind].index] = st.query(0, ind - 1);
            st.update(ind, 0);
        }
    }
    for (int i = 0; i < 2 * n; ++i) {
        int ind = pts[i].index;
        if (pts[i].type == 1) {
            st.update(ind, 1);
            contains[ranges[ind].index] = st.query(ind + 1, n - 1);
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << contains[i] << ' ';
    } std::cout << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << containedBy[i] << ' ';
    } std::cout << '\n';
}
