/*

CSES: Introductory Problems: Grid Paths

You have a 7x7 grid. You start at the top left square and want to end at the
bottom left square while visiting all squares only once. A path is described as
a string consisting of 48 moves (represented by L, R, U, and D). You are given
a description of a path but some of the moves are empty (represented by '?').
Determine how many unique paths fit this description.

Example Input:
??????R??????U??????????????????????????LD????D?

Example Output:
201

This problem can be solved with recursive backtracking. If we are on the i'th
move and the i'th character in the path description is filled in, try to make
that move. If the i'th character is not filled in (is '?'), then try to make
all 4 moves. One important optimization is to stop recursion if our path splits
the grid into 2 regions (if this happens, we won't be able to visit all the
squares). We can detect this if the square in front of us has been visited (or
is an edge), but the squares to our left and right have not been visited.
Another optimization is to stop recursion if we reach the end square (7,1)
before all other squares have been visited. We can also create a 9x9 grid
(instead of 7x7) and mark the edges as visited so we don't have to do any
bounds checking.

*/

#include <iostream>
#include <string>

std::string path;
bool visited[9][9] = { false };

bool valid(int row, int col) {
    if (visited[row][col])
        return false;
    bool U = visited[row - 1][col];
    bool D = visited[row + 1][col];
    bool L = visited[row][col - 1];
    bool R = visited[row][col + 1];
    if ((U && D && !L && !R) || (!U && !D && L && R))
        return false;
    return true;
}

int rec(int move, int row, int col) {
    if (row == 7 && col == 1)
        return move == 48;
    if (move >= 48 || !valid(row, col))
        return 0;
    visited[row][col] = true;
    int count = 0;
    switch (path[move]) {
        case 'U': count += rec(move + 1, row - 1, col); break;
        case 'D': count += rec(move + 1, row + 1, col); break;
        case 'L': count += rec(move + 1, row, col - 1); break;
        case 'R': count += rec(move + 1, row, col + 1); break;
        case '?':
            count += rec(move + 1, row - 1, col);
            count += rec(move + 1, row + 1, col);
            count += rec(move + 1, row, col - 1);
            count += rec(move + 1, row, col + 1);
    }
    visited[row][col] = false;
    return count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> path;
    for (int i = 0; i <= 8; ++i) {
        visited[i][0] = visited[0][i] = visited[8][i] = visited[i][8] = true;
    }
    std::cout << rec(0, 1, 1) << '\n';
}
