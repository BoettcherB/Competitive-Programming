/*

Consider a game where there are n children in a circle. During the game, every
other child is removed from the circle until there are no children left. In
which order will the children be removed?

Constraints:
 - 1 <= n <= 200,000

Example Input:
7

Example Output:
2 4 6 1 5 3 7

Solve this problem using a queue. Insert every number from 1 to n inclusive
into the queue. For each number popped off the queue, take turns adding the
number to the back of the queue and printing the number.

*/

#include <iostream>
#include <queue>
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    int n;
    std::cin >> n;
    std::queue<int> q;
    for (int i = 1; i <= n; ++i) {
        q.push(i);
    }
    bool print = false;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (print)
            std::cout << cur << ' ';
        else
            q.push(cur);
        print = !print;
    }
    std::cout << '\n';
}
