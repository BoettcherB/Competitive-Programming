/*

CSES: Dynamic Programming: Projects

There are n project, each with a start and end day [a, b] and a reward r. If
you choose to attend a project, you must attend it the entire time (including
the entire final day). What is the maximum reward you can earn?

Constraints:
    1 <= n <= 200,000
    1 <= a_i <= b_i <= 1,000,000,000
    1 <= p_i <= 1,000,000,000

Example Input:
4
2 4 4
3 6 6
6 8 2
5 7 3

Example Output:
7

This is an interval scheduling problem. First, sort the projects by the end
time. Let dp[i] be the maximum reward after considering only the first i
projects. If we choose not to attend project i, dp[i] = dp[i - 1]. If we choose
to attend project i, we need to find the largest index j such that project[j]'s
end time is < project[i]'s start time. Since the projects are sorted by end
time, we can use binary search for this. Once index j has been found, we simply
take the highest reward from all projects up to j, plus the reward for project
i: dp[i] = dp[j] + r_i.

Recurrence: dp[i] = max(dp[i - 1], dp[j] + r_i)
            where j = largest index where b_j < a_i

*/

#include <iostream>
#include <algorithm>
#include <vector>

struct Project {
    int a, b, p;
    bool operator<(const Project& other) const {
        return b < other.b;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<Project> proj(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> proj[i].a >> proj[i].b >> proj[i].p;
    }
    std::sort(proj.begin(), proj.end());
    std::vector<long long> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        Project p = { 0, proj[i].a, 0 };
        auto itr = std::lower_bound(proj.begin(), proj.end(), p);
        dp[i] = std::max(dp[i - 1], dp[--itr - proj.begin()] + proj[i].p);
    }
    std::cout << dp[n] << std::endl;
}
