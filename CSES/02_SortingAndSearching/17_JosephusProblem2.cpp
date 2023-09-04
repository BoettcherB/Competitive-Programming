/*

Consider a game where there are n children in a circle. During the game,
repeatedly k children are skipped and one child is removed from the circle.
In which order will the children be removed?

Constraints:
 - 1 <= n <= 200,000
 - 1 <= k <= 1,000,000,000

Example Input:
7 2

Example Output:
3 6 2 7 5 1 4

We can represent the circle as an array where a 1 means the child is present
and 0 means absent. We can find the index of the kth child from a current
position by finding the index where the prefix sum equals k. We also need to
update the array by marking the child as absent (update the value to 0 at that
index). We can do both of these operations quickly using a segment tree.

*/

#include <iostream>

const int N = 2e5 + 10;

class SegmentTree {
    int n;
    int tree[4 * N];

    void build(int cur, int l, int r) {
        if (l == r)
            tree[cur] = 1;
        else {
            int mid = (l + r) / 2;
            build(cur * 2, l, mid);
            build(cur * 2 + 1, mid + 1, r);
            tree[cur] = tree[cur * 2] + tree[cur * 2 + 1];
        }
    }

    void update(int cur, int l, int r, int index) {
        if (l == r)
            tree[cur] = 0;
        else {
            int mid = (l + r) / 2;
            if (index <= mid)
                update(cur * 2, l, mid, index);
            else
                update(cur * 2 + 1, mid + 1, r, index);
            tree[cur] = tree[cur * 2] + tree[cur * 2 + 1];
        }
    }

    int query(int cur, int l, int r, int k) {
        if (l == r)
            return l;
        int mid = (l + r) / 2;
        if (tree[cur * 2] >= k)
            return query(cur * 2, l, mid, k);
        return query(cur * 2 + 1, mid + 1, r, k - tree[cur * 2]);
    }

public:

    SegmentTree(int n) : n{ n } {
        build(1, 1, n);
    }

    void update(int index) {
        update(1, 1, n, index);
    }

    int query(int k) {
        return query(1, 1, n, k);
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    SegmentTree segtree(n);
    int pos = 0, remaining = n;
    while (remaining) {
        pos = (pos + k) % remaining--;
        int index = segtree.query(pos + 1);
        std::cout << index << '\n';
        segtree.update(index);
    }
    std::cout << '\n';
}
