/*

There is a street of length x. n traffic lights (each represented as an integer
p from 1 to x-1) are added to the street sequentially. Your task is to find the
longest stretch of road without a light after each addition.

Constraints:
 - 1 < x < 1,000,000,000
 - 1 <= n <= 200,000
 - 0 < p < x

Example Input:
8 3
3 6 2

Example Output:
5 3 3

This problem can be solved using 2 sets. The first set will hold the road
segments and their lengths sorted by position. The second set (a multiset) will
hold just the lengths. When we add a light, search the first set for the road
segment it will be added to and create 2 new road segments out of that segment
(one for each side of the light). As we do this, remove the length of the
original road segment from the second set and add the lengths of the 2 new road
segments. After each addition, print the last element in the second set.

*/

#include <iostream>
#include <set>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int x, n;
    std::cin >> x >> n;
    std::multiset<int> lengths = { x };
    std::set<std::pair<int, int>> roads = { {0, x} };
    for (int i = 0; i < n; ++i) {
        int light;
        std::cin >> light;
        auto itr = --roads.lower_bound({light, 0});
        std::pair<int, int> new1 = {itr->first, light - itr->first};
        std::pair<int, int> new2 = {light, itr->second - (light - itr->first)};
        lengths.erase(lengths.find(itr->second));
        lengths.insert(new1.second);
        lengths.insert(new2.second);
        roads.erase(itr);
        roads.emplace(new1);
        roads.emplace(new2);
        std::cout << *(--lengths.end()) << ' ';
    }
    std::cout << '\n';
}
