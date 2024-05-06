/*

There are n movies. You are given the start and end times (a and b) of all of
them. Determine the maximum number of movies that you can fully watch.

Constraints:
    1 <= n <= 200,000
    1 <= a < b <= 1,000,000,000

Example Input:
3
3 5
4 9
5 8

Example Output:
2

Sort the movies by their ending times. Loop through the movies while keeping
track of the time the previous watched movie ends (initially 0). If a movie
has already started (its start time is < the previous movie's end time), skip
to the next movie. If a movie starts after (or right at) the previous movie's
end time, watch that movie and set the end time to that movie's ending time.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

struct Movie {
    int start, end;
    bool operator<(const Movie& other) const {
        return end == other.end ? start < other.start : end < other.end;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    Movie movies[N];
    for (int i = 0; i < n; ++i) {
        std::cin >> movies[i].start >> movies[i].end;
    }
    std::sort(movies, movies + n);
    int res = 0, endTime = 0;
    for (int i = 0; i < n; ++i) {
        if (movies[i].start >= endTime) {
            endTime = movies[i].end;
            ++res;
        }
    }
    std::cout << res << '\n';
}
