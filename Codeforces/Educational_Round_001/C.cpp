#include <iostream>
#include <algorithm>
#include <cmath>

const int N = 1e5 + 10;
const long double PI = 3.141592653589793;

struct Vector {
    int x, y, index;
    long double angle;
    bool operator<(const Vector& other) const {
        return angle < other.angle;
    }
};

long double find_angle(long double x, long double y) {
    if (x == 0)
        return y > 0 ? PI / 2 : y < 0 ? 3 * PI / 2 : 0;
    if (y == 0)
        return x > 0 ? 0 : PI;
    long double angle = std::atan(std::abs(y / x));
    if (x < 0 && y > 0) angle = PI - angle;
    else if (x < 0 && y < 0) angle += PI;
    else if (x > 0 && y < 0) angle = 2 * PI - angle;
    return angle;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    Vector v[N];
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i].x >> v[i].y;
        v[i].index = i + 1;
        v[i].angle = find_angle(v[i].x, v[i].y);
    }
    std::sort(v, v + n);
    long double min_angle = v[0].angle + 2 * PI - v[n - 1].angle;
    int a = v[0].index, b = v[n - 1].index;
    for (int i = 1; i < n; ++i) {
        long double cur_angle = v[i].angle - v[i - 1].angle;
        if (cur_angle < min_angle) {
            min_angle = cur_angle;
            a = v[i - 1].index;
            b = v[i].index;
        }
    }
    std::cout << a << ' ' << b << '\n';
}
