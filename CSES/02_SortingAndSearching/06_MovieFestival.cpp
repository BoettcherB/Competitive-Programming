/*

There are n movies. You are given the start and end times (a and b) of all of
them. Determine the maximum number of movies that you can fully watch.

Constraints:
 - 1 <= n <= 200,000
 - 1 <= a < b <= 1,000,000,000

Example Input:
3
3 5
4 9
5 8

Example Output:
2

Sort the movies by their ending times. Loop through the movies while keeping
track of the current time (initially 0). If a movie has already started (its
start time is < the current time), skip to the next movie. If a movie starts
after (or right at) the current time, watch that movie and set the current time
to that movie's ending time.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::pair<int, int> movies[N];
    for (int i = 0; i < n; ++i) {
        std::cin >> movies[i].second >> movies[i].first;
    }
    std::sort(movies, movies + n);
    int cur_time = 0, seen = 0;
    for (int i = 0; i < n; ++i) {
        if (movies[i].second < cur_time)
            continue;
        ++seen;
        cur_time = movies[i].first;
    }
    std::cout << seen << '\n';
}
