/*

Problem Statement: https://usaco.org/index.php?page=viewproblem2&cpid=1398

Since 2 cows can be on the same y-value, the only way to fail the exercise is
if either the number of positive slopes or the number of negative slopes is <
n, since each upper right target requires a positive slope and each lower right
target requires a negative slope. The left targets (where x = x1) can be hit by
either a positive or negative slope. However, since we want to minimize the
difference between y-intercepts, it is optimal if the left targets with higher
y values are targeted with positive slopes, and the left targets with lower
y values are targeted with negative slopes. With this, we can simplify the
problem: let P be the set of targets that will be targeted by positive slopes,
and PS the set of positive slopes. If each target in P is assigned a slope in 
PS (or each slope assigned a target) optimally, what is the best (maximum)
minimum y-intercept?

An O(n^2) solution: Sort the slopes in PS. Then, for each slope, loop through
each target in P (that has not already been assigned a slope), find the one
that results in the highest y intercept, and assign the slope to that target.
The answer for this subproblem is the minimum y-intercept value.

However, we need an O(nlogn) solution. For this, we can use binary search on
all the possible y-intercepts (-1e18 to 1e18). Given a y-intercept value y,
determine if it is possible to assign the targets in such a way that the lowest
y-intercept value is >= y. To do this, we can sort the slopes, and then for
each target t = {tx, ty}, find the slope that results in the lowest y-intercept
value that is still >= y. (For this we can use another binary search function,
such as upper_bound). y = mx + b; m = (ty - y) / tx; search for the highest
slope in PS that is <= (ty-y)/tx and remove it. If there is none, then it is
impossible for y to be the best y-intercept.

For the negative slopes (NS) and their targets (N), the problem is exactly the
same except we are trying to find the minimum y-intercept. We can easily
convert this problem into the maximum version by flipping the signs of all the
slopes in NS and all the y-values of the targets in N. Then, once we get an 
answer y, flip its sign as well. The answer to the overall problem is the
difference between the 2 y-intercepts of the sub-problems.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

typedef std::vector<std::pair<long long, long long>> vec;

bool check(vec& targets, std::multiset<long long>& slopes, long long y) {
    for (const auto& t : targets) {
        auto itr = slopes.upper_bound((t.second - y) / t.first);
        if (itr == slopes.begin())
            return false;
        slopes.erase(--itr);
    }
    return true;
}

long long maximize(vec& targets, std::vector<long long>& slopes) {
    long long l = -1.1e18, r = 1.1e18; // [l, r)
    while (l + 1 < r) {
        long long mid = (r - l) / 2 + l;
        std::multiset<long long> s(slopes.begin(), slopes.end());
        (check(targets, s, mid) ? l : r) = mid;
    }
    return l;
}

long long minimize(vec& targets, std::vector<long long>& slopes) {
    for (auto& t : targets) t.second = -t.second;
    for (auto& s : slopes) s = -s;
    return -maximize(targets, slopes);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, x1;
        std::cin >> n >> x1;
        std::vector<long long> x2(n), y1(n), y2(n), PS, NS;
        for (int i = 0; i < n; ++i) {
            std::cin >> y1[i] >> y2[i] >> x2[i];
        }
        for (int i = 0; i < 4 * n; ++i) {
            int x;
            std::cin >> x;
            (x < 0 ? NS : PS).push_back(x);
        }
        int negcount = (int) NS.size();
        if (negcount < n || negcount > 3 * n) {
            std::cout << -1 << '\n';
            continue;
        }
        vec close(2 * n); // targets with x = x1
        for (int i = 0; i < n; ++i) {
            close[i] = { x1, y1[i] };
            close[i + n] = { x1, y2[i] };
        }
        std::sort(close.begin(), close.end());
        vec N(close.begin(), close.begin() + negcount - n);
        vec P(close.begin() + negcount - n, close.end());
        for (int i = 0; i < n; ++i) {
            N.push_back({ x2[i], y2[i] });
            P.push_back({ x2[i], y1[i] });
        }
        std::cout << minimize(N, NS) - maximize(P, PS) << '\n';
    }
}
