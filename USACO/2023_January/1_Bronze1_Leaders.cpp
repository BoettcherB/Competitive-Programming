/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1275

This problem is much easier after a few realizations. Firstly, there cannot be
2 cows that both have each other in their list. A cow's list can only cover
cows to their right. Therefore, one of the leaders must have all cows of their
breed in their list (it is impossible for both leaders to only be leaders
because the other leader is in their list). Secondly, for both breeds there can
only be 1 cow that has all cows in their list. This is again because a list can
only cover cows to the right.

First determine which G cow (if any) contains all other G cows in their list
and which H cow (if any) contains all other H cows in their list. This can be
done by splitting the G and H cows into vectors and checking if the first cow
of each vector contains the last cow. If we found a G cow, search through all
H cows to see if any contain that G cow in their list. If so, this is a
potential leader pair. Do the same for the H cow. Also, if we found both a G
and an H cow, that is a potential leader pair.

*/

#include <iostream>
#include <string>
#include <vector>

const int N = 1e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, arr[N];
    std::string str;
    std::cin >> n >> str;
    std::vector<std::pair<int, int>> H, G;
    for (int i = 1; i <= n; ++i) {
        std::cin >> arr[i];
        if (str[i - 1] == 'G')
            G.emplace_back(i, arr[i]);
        else
            H.emplace_back(i, arr[i]);
    }
    int g_idx = (G[0].second >= G.back().first ? G[0].first : 0);
    int h_idx = (H[0].second >= H.back().first ? H[0].first : 0);
    int res = g_idx && h_idx;
    for (const auto& g : G) {
        res += g.first < h_idx && g.second >= h_idx && g.first != g_idx;
    }
    for (const auto& h : H) {
        res += h.first < g_idx && h.second >= g_idx && h.first != h_idx;
    }
    std::cout << res << '\n';
}
