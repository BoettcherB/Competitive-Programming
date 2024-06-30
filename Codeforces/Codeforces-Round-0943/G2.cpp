/*

Problem Statement: https://codeforces.com/contest/1968/problem/G2

This problem is similar to the previous one (G1) except now we need to find the
answer for all values of k between some range (L, R). For this, we can use the
same realization as in the previous problem: as the number of subarrays (k)
increases, LCP(S, k) will decrease. We can see this in the sample output: the
values of f are decreasing. This means that if LCP(S, i) == LCP(S, j), then all
indexes in between i and j will also equal LCP(S, i). We can use an algorithm
similar to mergesort where we recursively evaluate a range [l, r]. If l-1 and
r+1 have been evaluated and are the same value, we can fill in all values in
the range with that value. Otherwise, evaluate the middle element and split the
range in half. In total, the runtime is O(n*log(n)*log(n)).

*/

#include <iostream>
#include <vector>
#include <string>

std::vector<int> res, z;
int n, L, R;
std::string str;

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

int binsearch(int k) {
    int l = 0, r = n + 1; // [l, r)
    while (l + 1 < r) {
        int x = (l + r) / 2;
        int substr_count = 1;
        for (int i = x; i < (int) str.length(); ++i) {
            if (z[i] >= x) {
                ++substr_count;
                i += x - 1;
            }
        }
        (substr_count >= k ? l : r) = x;
    }
    return l;
}

void fill(int l, int r) {
    if (l > r) return;
    if (l - 1 > L && r + 1 < R && res[l - 1] == res[r + 1]) {
        for (int i = l; i <= r; ++i)
            res[i] = res[l - 1];
        return;
    }
    int x = (l + r) / 2;
    res[x] = binsearch(x);
    fill(l, x - 1);
    fill(x + 1, r);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        std::cin >> n >> L >> R >> str;
        res = std::vector<int>(n + 1);
        z = z_function(str);
        fill(L, R);
        for (int i = L; i <= R; ++i) {
            std::cout << res[i] << " \n"[i == R];
        }
    }
}
