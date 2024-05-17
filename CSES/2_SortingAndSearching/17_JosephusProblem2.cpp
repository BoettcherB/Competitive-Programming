/*

Consider a game where there are n children in a circle. During the game,
repeatedly k children are skipped and one child is removed from the circle.
In which order will the children be removed?

Constraints:
    1 <= n <= 200,000
    1 <= k <= 1,000,000,000

Example Input:
7 2

Example Output:
3 6 2 7 5 1 4

We can represent the circle as an array where 1 means the child is present and
0 means absent. Let pos be the index [0, n) of the child that is to be removed,
and let rem be the number of children remaining in the circle. The next child
removed will be i = (pos + k) % rem (the i'th child in the circle). In order
to find the index of the i'th child (i.e. the i'th 1 in an array), we can use
prefix sums. However, we also need to be able to update 1's to 0's when a child
is removed. Both of these operations can be performed with a segment tree.

Let's say we want to find the i'th 1 in a segment and the current segment has 8
1's (both the left and right halves have 4). If i <= 4, go to the left segment
and search for the i'th 1. If i > 4, go to the right segment and search for the
(i-4)'th 1.

*/

#include <iostream>

const int N = 2e5 + 10;

class SegmentTree {
    int n, tree[4 * N];

    void build(int cur, int tl, int tr) {
        if (tl == tr) {
            tree[cur] = 1;
        } else {
            int mid = (tl + tr) / 2;
            build(cur * 2, tl, mid);
            build(cur * 2 + 1, mid + 1, tr);
            tree[cur] = tree[cur * 2] + tree[cur * 2 + 1];
        }
    }

    void update(int cur, int tl, int tr, int pos) {
        if (tl == tr) {
            tree[cur] = 0;
        } else {
            int mid = (tl + tr) / 2;
            if (pos <= mid) {
                update(cur * 2, tl, mid, pos);
            } else {
                update(cur * 2 + 1, mid + 1, tr, pos);
            }
            tree[cur] = tree[cur * 2] + tree[cur * 2 + 1];
        }
    }

    int query(int cur, int tl, int tr, int k) {
        if (tl == tr)
            return tl;
        int mid = (tl + tr) / 2;
        if (tree[cur * 2] >= k) {
            return query(cur * 2, tl, mid, k);
        } else {
            return query(cur * 2 + 1, mid + 1, tr, k - tree[cur * 2]);
        }
    }

public:
    SegmentTree(int n) : n{ n } {
        build(1, 1, n);
    }

    void update(int pos) {
        update(1, 1, n, pos);
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
    SegmentTree st(n);
    int pos = 0, rem = n;
    while (rem > 0) {
        pos = (pos + k) % rem--;
        int index = st.query(pos + 1);
        st.update(index);
        std::cout << index << ' ';
    }
    std::cout << '\n';
}
