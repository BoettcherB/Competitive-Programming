/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1276

For this problem the inputs are small enough that an O(2^n) solution is
possible. We can use brute force to try all 2^M combinations of AC units. Out
of every combination that satisfies the problem's requirements (all stalls are
cooled an adequate amount), we choose the one with lowest cost.

A simple method is to use recursion. For each AC unit either skip it and move
on to the next one, or factor in its cooling and cost. If we reach the last AC
unit and all cows are cooled adequately, then this is a valid combination.

*/

#include <iostream>

const int N = 110;
const int INF = 2e9;
int n, m, stalls[N];
int left[N], right[N], cost[N], AC_cooling[N];

int solve(int index, int cooling[N]) {
    if (index == m) {
        for (int i = 1; i <= 100; ++i)
            if (cooling[i] < stalls[i])
                return INF;
        return 0;
    }
    int newCooling[N];
    for (int i = 1; i <= 100; ++i) {
        newCooling[i] = cooling[i];
        if (i >= left[index] && i <= right[index])
            newCooling[i] += AC_cooling[index];
    }
    int cost_with = solve(index + 1, newCooling) + cost[index];
    int cost_without = solve(index + 1, cooling);
    return std::min(cost_with, cost_without);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int s, t, c;
        std::cin >> s >> t >> c;
        for (int j = s; j <= t; ++j)
            stalls[j] = c;
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> left[i] >> right[i] >> AC_cooling[i] >> cost[i];
    }
    int cooling[N] = {};
    std::cout << solve(0, cooling) << '\n';
}
