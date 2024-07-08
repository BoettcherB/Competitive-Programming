#include <iostream>

bool solve() {
    int a1, b1, c1, d1, e1, f1;
    int a2, b2, c2, d2, e2, f2;
    std::cin >> a1 >> b1 >> c1 >> d1 >> e1 >> f1;
    std::cin >> a2 >> b2 >> c2 >> d2 >> e2 >> f2;
    if (a1 > a2 && a1 >= d2) return false;
    if (b1 > b2 && b1 >= e2) return false;
    if (c1 > c2 && c1 >= f2) return false;
    if (d1 <= a2 && d1 < d2) return false;
    if (e1 <= b2 && e1 < e2) return false;
    if (f1 <= c2 && f1 < f2) return false;
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cout << (solve() ? "Yes" : "No") << '\n';
}
