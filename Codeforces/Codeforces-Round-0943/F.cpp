/*

Problem Statement: https://codeforces.com/contest/1968/problem/F

For this problem, we are given queries over an array. However, there are no
updates on the array so a segment tree is not needed. Instead, we can just use
prefix sums (or in this case, prefix xors).

The first observation we need to make is that we never need to split up a
segment into more than 3 parts. This is because x ^ x ^ x = x. If there is more
than 3 parts, we can always condense it down into either 2 or 3 parts.

Now, for each segment [l, r], we either need to divide it into 2 parts or 3
parts. If we divide it into 2 parts, then there is an index k (l < k < r) where
xor[l, k] == xor[k+1, r]. Using prefix xors: p[k] ^ p[l-1] == p[r] ^ p[k]. This
simplifies to p[l-1] == p[r]. If p[l-1] == p[r], then we can split the segment
into 2 parts. To divide the segment into 3 parts, we need 2 indexes a and b
such that xor[l, a] == xor[a+1, b] == xor[b+1, r]. Using prefix sums: we need
p[a] ^ p[l-1] == p[b] ^ p[a], and p[b] ^ p[a] == p[r] ^ p[b]. These simplify to
p[l-1] == p[b] and p[a] == p[r]. In other words, we need to find an index a
where a < r and p[a] == p[r], and we need to find an index b where b > l-1 and
p[b] == p[l-1]. For this, we can use a map to store the indices for each
distinct value in the array p. Then, we can use a binary search function to
find indices a and b, if they exist.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
	int tc;
	std::cin >> tc;
	while (tc--) {
		int n, q;
		std::cin >> n >> q;
        std::vector<int> prefix(n + 1);
		std::map<int, std::vector<int>> ind;
		ind[0].push_back(0);
		for(int i = 1; i <= n; ++i) {
			std::cin >> prefix[i];
			prefix[i] ^= prefix[i - 1];
			ind[prefix[i]].push_back(i);
		}
		while (q--) {
			int l, r;
			std::cin >> l >> r;
			if (prefix[l - 1] == prefix[r])
				std::cout << "YES" << '\n';
			else {
                std::vector<int>& I1 = ind[prefix[l - 1]];
                std::vector<int>& I2 = ind[prefix[r]];
			    int a = *(--std::lower_bound(I1.begin(), I1.end(), r));
			    int b = *std::lower_bound(I2.begin(), I2.end(), l);
			    std::cout << (a > b ? "YES" : "NO") << '\n';
            }
		}
		if (tc) std::cout << '\n';
	}
}
