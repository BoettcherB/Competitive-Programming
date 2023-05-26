/*

You are given n cubes with sizes x1...xn and your task is to make towers out of
them. A cube can only be placed on a larger cube, or it can be used as the base
of a new tower. The cubes must be processed in order. What is the minimum
number of towers possible?

Constraints:
 - 1 <= n <= 200,000
 - 1 <= x <= 1,000,000,000

Example Input:
5
3 8 2 1 5

Example Output:
2

For every cube i with size x, it is always best to place cube i on the tower
with the smallest top whose size is still greater than x. We can keep a
multiset which holds the sizes of the tops of each tower. When adding a new
cube, search for a tower whose top is > x, remove it, and then add x. If cube
i needs its own tower, just add it to the set.

*/

#include <iostream>
#include <set>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::multiset<int> s;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        auto itr = s.upper_bound(a);
        if (itr != s.end())
            s.erase(itr);
        s.insert(a);
    }
    std::cout << s.size() << std::endl;
}
