/*

There are n movies in a festival, each with a start time 'a' and an end time
'b'. There are k participants of the festival. How many different movies can
the participants fully watch if they act optimally? If one movie ends at the
same time as another movie starts, a single participant can watch both movies.

Constraints
    1 <= k <= n <= 200,000
    1 <= a < b <= 1,000,000,000

Example Input:
5 2
1 5
8 10
3 6
2 5
6 9

Example Output:
4

We can solve this problem by keeping a set s of the times when each participant
will be done with their current movie (initially, these times are 0 for all k
participants). Sort the movies by end time and loop through them. For each
movie, we can check the set s to see if there is a participant who is able to
watch this movie. If so, there will be an end time in s that is <= the current
movie's start time. If there are multiple participants who could watch the
current movie, choose the one with the latest end time. Remove that end time
from s and add the current movie's end time. Do this for all movies.

*/

#include <iostream>
#include <algorithm>
#include <set>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    std::pair<int, int> movies[N];
    std::multiset<int> s;
    for (int i = 0; i < n; ++i) {
        std::cin >> movies[i].second >> movies[i].first;
        if (i < k)
            s.insert(0);
    }
    std::sort(movies, movies + n);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        auto itr = s.upper_bound(movies[i].second);
        if (itr != s.begin()) {
            s.erase(--itr);
            s.insert(movies[i].first);
            ++res;
        }
    }
    std::cout << res << '\n';
}
