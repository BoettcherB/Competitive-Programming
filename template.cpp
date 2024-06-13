#include <iostream>
#include <vector>
#include <algorithm>

template <class T> struct rge { T b, e; };
template <class T> rge<T> range(T i, T j) { return rge<T>{i, j}; }
template <class T> auto dud(T* x) -> decltype(std::cerr << *x, 0);
template <class T> char dud(...);
struct debug {
    ~debug() { std::cerr << std::endl; }
    template <class T>
    typename std::enable_if<sizeof(dud<T>(0)) != 1, debug&>::type operator<<(T i) {
        std::cerr << std::boolalpha << i;
        return *this;
    }
    template <class T>
    typename std::enable_if<sizeof(dud<T>(0)) == 1, debug&>::type operator<<(T i) {
        return *this << range(std::begin(i), std::end(i));
    }
    template <class T1, class T2>
    debug& operator<<(std::pair<T1, T2> p) {
        return *this << "(" << p.first << ", " << p.second << ")";
    }
    template <class c> debug& operator<< (rge<c> d) {
        *this << "[";
        for (auto it = d.b; it != d.e; ++it)
            *this << ", " + 2 * (it == d.b) << *it;
        return *this << "]";
    }
};
#define RED "\033[31m"
#define RESET "\033[0m"
#ifdef DB_LOCAL
#define pprint(x) (debug() << RED << " [" << #x ": " << x << "] " << RESET)
#else
#define pprint(x)
#endif

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
}
