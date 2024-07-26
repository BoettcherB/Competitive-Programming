/*

Problem Statement: https://usaco.org/index.php?page=viewproblem2&cpid=1253

The inputs (N <= 100, M <= 100) are small enough that we can use brute force to
solve this problem. For each index 0 <= i < n of the input strings, we can
check if we are able to create an if statement on that index by checking if all
input strings with the same value at that index have the same output value. For
example, if all the remaining input strings that have b[i] == 0 have an output
of 0, then we can create an if statement. Similarly, if all the remaining input
strings that have b[i] == 0 have an output of 1, or if all strings where b[i]
== 1 have an output of 0, or if all strings where b[i] == 1 have an ouput of 1,
then we can create an if statement. If we can create an if statement on a set
of input strings, then we can remove those strings from our list of remaining
strings. If we are able to remove all strings, then we can print OK. 

*/

#include <iostream>
#include <string>
#include <list>

std::list<std::pair<std::string, int>> inputs;

bool create_if(int index, char val) {
    int out = -1;
    for (const auto& p : inputs) {
        if (p.first[index] == val) {
            if (out == -1)
                out = p.second;
            if (out != p.second)
                return false;
        }
    }
    auto itr = inputs.begin();
    while (itr != inputs.end()) {
        if (itr->first[index] == val)
            itr = inputs.erase(itr);
        else
            ++itr;
    }
    return out != -1;
}

bool solve(int n) {
    for (int i = 0; i < n; ++i) {
        if (create_if(i, '0') || create_if(i, '1'))
            i = -1;
    }
    return inputs.empty();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        inputs.clear();
        int n, m;
        std::cin >> n >> m;
        for (int i = 0; i < m; ++i) {
            std::string in;
            int out;
            std::cin >> in >> out;
            inputs.emplace_back(in, out);
        }
        std::cout << (solve(n) ? "OK" : "LIE") << '\n';
    }
}
