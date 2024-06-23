/*

CSES: Introductory Problems: Tower Of Hanoi

Solve the Tower of Hanoi puzzle. You are given an integer n which represents
the number of disks in the left tower. Your goal is to move all the disks to
the right tower using the middle tower. You can only move the top disk off of
one of the towers to another tower, and you cannot place a larger disk on top
of a smaller disk. Print out the minimum number of moves needed to solve this 
puzzle, and a description of each move.

Constraints:
    1 <= n <= 16

Example Input:
2

Example Output:
3
1 2
1 3
2 3

Generally, we can move a stack of n disks from one tower to another by first
moving the top n-1 disks to the middle tower, then moving the largest disk to
the right tower, then moving the top n-1 disks from the middle tower to the
right tower. In order to move the top n-1 disks from the left tower to the
middle tower, we need to move the top n-2 disks to the right tower, then move
the n-1 disk to the middle tower, then the top n-2 disks to the middle tower.
This continues on until we have a stack of size 1, which we can just move
straight to its destination.

We can use recursion to easily replicate this process. We can define a function
move(source, dest, size) which moves a stack of 'size' disks from 'source' to
'dest'. source and dest are just integers from 1-3 representing the 3 towers.
We can move a tower of size n from the left to the right with move(1, 3, n).
This will first move the top n-1 disks to the middle tower (move(1, 2, n-1)),
then move the bottom disk to the right (which we can just print), then move the
top n-1 disks to the right tower (move(2, 3, n-1)). We can use XOR to find the
'middle' tower (the one that isn't the source or the destination). This works
because 1^2 = 3, 1^3 = 2, and 2^3 = 1.

We can use algebra to find the number of moves required to solve the puzzle.
moves(k) is the number of moves required to move a tower of size k. moves(k) =
2*moves(k-1)+1. A tower of size 1 requires 1 move. A tower of size 2 requies 3
moves. Size 3 requires 7 moves. Size 4 requires 15 moves. There is a clear
pattern where moves(k) = 2^k - 1.

*/

#include <iostream>

void move(int source, int dest, int size) {
    int middle = source ^ dest;
    if (size > 0) {
        move(source, middle, size - 1);
        std::cout << source << ' ' << dest << '\n';
        move(middle, dest, size - 1);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::cout << ((1 << n) - 1) << '\n';
    move(1, 3, n);
}
