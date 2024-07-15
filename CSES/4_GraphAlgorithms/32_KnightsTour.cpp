/*

You are given the starting position of a knight on an 8x8 chessboard. Your task
is to find a sequence of moves such that the knight visits every square exactly
once. Print out a grid that shows the knight's moves.

Constraints:
    1 <= x, y <= 8

Example Input:
2 1

Example Output:
8 1 10 13 6 3 20 17 
11 14 7 2 19 16 23 4 
26 9 12 15 24 5 18 21 
49 58 25 28 51 22 33 30 
40 27 50 59 32 29 52 35 
57 48 41 44 37 34 31 62 
42 39 46 55 60 63 36 53 
47 56 43 38 45 54 61 64

If we think of squares as vertices and knight moves as edges, then this problem
is asking us to find a Hamiltonian path through the board. This can be done
using recursive backtracking. Since there are 64 squares and (up to) 8 possible
knight moves per square, this algorithm could be O(8^64). However, if we always
choose to move to the square with the fewest remaining moves, we can achieve a
time complexity that is basically O(n^2). This is known as Warnsdorf's Rule and
it eliminates most of the backtracking, since squares with 0 or 1 moves left
will be visited immediately.

*/

#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned long long uint64;
std::vector<uint64> moves(64);
std::vector<int> res(64);

bool rec(int pos, uint64 bitboard, int move) {
    bitboard |= 1ULL << pos;
    res[pos] = move;
    if (move == 64)
        return true;
    uint64 curMoves = moves[pos] & ~bitboard;
    std::pair<int, int> moveCounts[8];
    int mv = 0;
    while (curMoves > 0) {
        int to = __builtin_ctzll(curMoves);
        moveCounts[mv++] = {__builtin_popcountll(moves[to] & ~bitboard), to };
        curMoves &= curMoves - 1;
    }
    std::sort(moveCounts, moveCounts + mv);
    for (int i = 0; i < mv; ++i) {
        if (rec(moveCounts[i].second, bitboard, move + 1))
            return true;
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int dx[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };
    int dy[8] = { 1, -1, 2, -2, 2, -2, 1, -1 };
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            for (int i = 0; i < 8; ++i) {
                int X = x + dx[i], Y = y + dy[i];
                if (X >= 0 && X < 8 && Y >= 0 && Y < 8)
                    moves[x * 8 + y] |= 1ULL << (X * 8 + Y);
            }
        }
    }
    int x, y;
    std::cin >> y >> x;
    rec(--x * 8 + --y, 0, 1);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cout << res[i * 8 + j] << ' ';
        }
        std::cout << '\n';
    }
}
