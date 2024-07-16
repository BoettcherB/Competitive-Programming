#include <iostream>
#include <list>
#include <set>
    
typedef std::pair<std::list<int>, std::list<int>> State;
    
struct CompareStates {
    bool operator()(const State& s1, const State& s2) const {
        auto l1 = s1.first, l2 = s2.first;
        if (l1.size() != l2.size()) {
            return l1.size() < l2.size();
        }
        auto itr1 = l1.begin(), itr2 = l2.begin();
        while (itr1 != l1.end()) {
            if (*itr1 != *itr2)
                return *itr1 < *itr2;
            ++itr1; ++itr2;
        }
        l1 = s1.second, l2 = s2.second;
        itr1 = l1.begin(), itr2 = l2.begin();
        while (itr1 != l1.end()) {
            if (*itr1 != *itr2)
                return *itr1 < *itr2;
            ++itr1; ++itr2;
        }
        return false;
    }
};
    
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, x, c;
    std::cin >> n >> x;
    std::list<int> l1, l2;
    for (int i = 0; i < x; ++i) {
        std::cin >> c;
        l1.push_back(c);
    }
    std::cin >> x;
    for (int i = 0; i < x; ++i) {
        std::cin >> c;
        l2.push_back(c);
    }
    std::set<State, CompareStates> seen;
    int moves = 0;
    while (!l1.empty() && !l2.empty()) {
        ++moves;
        if (seen.count({ l1, l2 })) {
            std::cout << -1 << '\n';
            return 0;
        }
        seen.emplace(l1, l2);
        if (l1.front() > l2.front()) {
            l1.push_back(l2.front());
            l1.push_back(l1.front());
        } else {
            l2.push_back(l1.front());
            l2.push_back(l2.front());
        }
        l1.pop_front();
        l2.pop_front();
    }
    std::cout << moves << ' ' << (l1.empty() ? 2 : 1) << '\n';
}
