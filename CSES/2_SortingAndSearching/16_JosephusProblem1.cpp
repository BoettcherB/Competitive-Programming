/*

Consider a game where there are n children in a circle. During the game, every
other child is removed from the circle until there are no children left. In
which order will the children be removed?

Constraints:
    1 <= n <= 200,000

Example Input:
7

Example Output:
2 4 6 1 5 3 7

Solve this problem using a list. Insert every number from 1 to n inclusive into
the list. Loop through the list, printing and erasing every other number, until
the list is empty.

Another simple way to solve this is to use a queue. For every number popped off
the front of the queue, take turns pushing that number to the back of the queue
and printing it.

*/

#include <iostream>
#include <list>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::list<int> list;
    for (int i = 1; i <= n; ++i) {
        list.push_back(i);
    }
    auto itr = list.begin();
    bool skip = true;
    while (!list.empty()) {
        if (skip) {
            ++itr;
        } else {
            std::cout << *itr << ' ';
            itr = list.erase(itr);
        }
        if (itr == list.end()) {
            itr = list.begin();
        }
        skip = !skip;
    }
    std::cout << '\n';
}
