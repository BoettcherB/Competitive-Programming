/*

Problem Statement: https://atcoder.jp/contests/abc354/tasks/abc354_d

We can see that the pattern repeats every 4 units along the x-axis. One method
to solve this problem is to 'shift' the coordinates A and C to the left so that
they are multiples of 4. This puts them at the start of the pattern. To shift a
coordinate x to the left, we need to compute the area between the original
position and the new position. There are 3 cases: x % 4 == 1, x % 4 == 2, and
x % 4 == 3. For each of these cases, we need to factor in the y-coordinates to
calculate the correct area. If we shift A to the left, we need to decrease our
answer by the area gained during the shift, and if we shift C to the left, we
need to increase our answer by the area lost during the shift. Once A and C are
multiples of 4, it is easy to compute the final answer: each row of the plane
has 4 triangles in every 4x1 repeat of the pattern, so our answer is
(C-A) / 4 * 4 * (D - B).

*/

#include <iostream>

long long mod(long long val, long long m) {
    return (val % m + m) % m;
}

long long shift(int pos, int B, int D) {
    long long res = 0, ydiff = D - B;
    if (mod(pos, 4) == 1) {
        res += ydiff / 2 * 3;
        if (mod(B, 2) == 0 && mod(D, 2) == 1)
            res += 2;
        else if (mod(B, 2) == 1 && mod(D, 2) == 0)
            res += 1;
    }
    else if (mod(pos, 4) == 2)
        res += ydiff * 3;
    else if (mod(pos, 4) == 3) {
        res += ydiff / 2 * 7;
        if (mod(B, 2) == 0 && mod(D, 2) == 1)
            res += 3;
        else if (mod(B, 2) == 1 && mod(D, 2) == 0)
            res += 4;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long  A, B, C, D;
    std::cin >> A >> B >> C >> D;
    long long res = shift(C, B, D) - shift(A, B, D);
    A -= mod(A, 4);
    C -= mod(C, 4);
    res += (D - B) * 4 * ((C - A) / 4);
    std::cout << res << '\n';
}
