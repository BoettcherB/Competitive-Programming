#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::pair<std::string, int>> people(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> people[i].first >> people[i].second;
        sum += people[i].second;
    }
    std::sort(people.begin(), people.end());
    std::cout << people[sum % n].first << '\n';
}
