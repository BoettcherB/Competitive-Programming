/*

There are n tasks that we have to process, one after the other, and each task
has a duration and a deadline. The reward for completing a task is d - f where
d is the deadline and f is the time the task is finished. What is the maximum
possible reward after processing all tasks?

Constraints
    1 <= n <= 200,000
    1 <= duration, deadline <= 1,000,000

Example Input:
3
6 10
8 15
5 12

Example Output:
2

The only thing that matters is that the quicker tasks (those with a shorter
duration) are completed first. Sort tasks by duration and then sum up the
rewards for each task.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

struct Task {
    int duration, deadline;
    bool operator<(const Task& other) const {
        return duration < other.duration;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    Task tasks[N];
    for (int i = 0; i < n; ++i) {
        std::cin >> tasks[i].duration >> tasks[i].deadline;
    }
    std::sort(tasks, tasks + n);
    long long reward = 0, time = 0;
    for (int i = 0; i < n; ++i) {
        time += tasks[i].duration;
        reward += tasks[i].deadline - time;
    }
    std::cout << reward << '\n';
}
