/*

Problem Statement: https://codeforces.com/contest/1968/problem/G1

We want to divide a string S into k substrings such that the longest common
prefix (LCP(S, k)) of the k substrings is maximized.

To start off, we have to realize that if it is possible to divide S into k
substrings such that LCP(S, k) == x, then it is also possible to divide S into
k substrings such that LCP(S, k) < x (and if x is optimal, it is not possible
for LCP(S, k) to be > x). Therefore, we can use binary search to find the
optimal value x.

Within the binary search, we have a value x and we need to determine if there
are at least k substrings equal to the length-x prefix of S. Unfortunately, 
using the std::string::find() method would be O(n^2). Instead, we need to use
an algorithm which computes the z-function of S, which is a length n array z
where z[i] = the length of the longest substring starting at position i that
matches the prefix of S. Once we have z, we can loop through each value and 
count the number of positions where z[i] >= x. This algorithm runs in O(n).

*/

#include <iostream>
#include <vector>
#include <string>

std::vector<int> z_function(const std::string& s) {
    int n = s.length();
    std::vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i < r) {
            z[i] = std::min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, k, k2;
        std::string str;
        std::cin >> n >> k >> k2 >> str;
        std::vector<int> z = z_function(str);
        int l = 0, r = n + 1; // [l, r)
        while (l + 1 < r) {
            int x = (l + r) / 2; // lcp
            int substr_count = 1;
            for (int i = x; i < (int) str.length(); ++i) {
                if (z[i] >= x) {
                    ++substr_count;
                    i += x - 1;
                }
            }
            (substr_count >= k ? l : r) = x;
        }
        std::cout << l << '\n';
    }
}
