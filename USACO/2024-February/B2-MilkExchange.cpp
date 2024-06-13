/*

Problem Statement: https://usaco.org/index.php?page=viewproblem2&cpid=1396

The type of graph described in this problem is a functional graph. In these
graphs, each node has exactly 1 out-edge. Functional graphs are comprised of
components, each with a cycle and some paths leading to it. In this problem,
the components are substrings with some number of 'R' followed by some number
of 'L' (ex: RRRLLLLL). In each componenet, there are two paths leading to a
cycle of size 2 (the cycle is when the two sides meet: "RL"). The milk buckets
of the cows on the cycle will always remain full because they will pass milk
back and forth. All other cows will pass milk towards the cycle. For each path
leading to the cycle, exactly 1 cup of milk will be lost every minute, until
all cows on the path are out of milk. The cow closest to the cycle will try to
pass a cup to the cow on the cycle, which will be lost because the cycle is
always full. The cows furthest from the cycle will be depleted first. For each
path, m cups will be lost after m minutes.

For each component, split it into 3 parts: the right path, the cycle, and the
left path. For the right and left paths, sum up the capacities of these cows,
subtract m (while avoiding going negative), and add these to the result. For
the 2 cows on the cycle, add their capacities to the result.

*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

template<class T>
long long sum(T start, T end, int m) {
    if (start >= end) return 0;
    long long s = std::accumulate(start, end, 0LL);
    return std::max(s - m, 0LL);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::string str;
    std::cin >> n >> m >> str;
    std::vector<int> cap(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cap[i];
    }
    if (str == std::string(n, 'R') || str == std::string(n, 'L')) {
        std::cout << std::accumulate(cap.begin(), cap.end(), 0LL) << '\n';
        return 0;
    }
    int rot = str.find("LR") + 1;
    std::rotate(str.begin(), str.begin() + rot, str.end());
    std::rotate(cap.begin(), cap.begin() + rot, cap.end());
    std::vector<std::string> comps;
    int start = 0;
    while (start < n) {
        int end = str.find("LR", start);
        if (end == (int) std::string::npos)
            end = n - 1;
        comps.push_back(str.substr(start, end - start + 1));
        start = end + 1;
    }
    long long res = 0;
    int index = 0;
    for (const std::string& cur : comps) {
        int R = std::count(cur.begin(), cur.end(), 'R') - 1;
        auto cap_start = cap.begin() + index;
        res += cap[index + R] + cap[index + R + 1];
        res += sum(cap_start, cap_start + R, m);
        res += sum(cap_start + R + 2, cap_start + cur.length(), m);
        index += cur.length();
    }
    std::cout << res << '\n';
}
