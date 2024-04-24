/*

You are given a list of n integers [x1...xn]. Determine the number of distinct
values in the list.

Constraints:
    1 <= n <= 200,000
    1 <= x <= 1,000,000,000

Example Input:
5
2 3 2 2 3

Example Output:
2

We can solve this problem with a set data structure. If we add all the numbers
to a set, it will automatically remove duplicates. The answer is the size of
the set after adding all numbers.

Another method is to sort the array of numbers (arr), then find the number of
positions i where arr[i] != arr[i-1]. The answer is this amount plus 1.

*/

#include <iostream>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::set<int> s;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        s.insert(x);
    }
    std::cout << s.size() << '\n';
}
