#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct Card {
    int index, strength, cost;
    bool operator<(const Card& other) const {
        return strength > other.strength;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<Card> cards(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cards[i].strength >> cards[i].cost;
        cards[i].index = i + 1;
    }
    std::sort(cards.begin(), cards.end());
    int minCost = 2e9;
    std::set<int> kept;
    for (int i = 0; i < n; ++i) {
        if (cards[i].strength == cards[0].strength || cards[i].cost <= minCost)
            kept.insert(cards[i].index);
        minCost = std::min(minCost, cards[i].cost);
    }
    std::cout << kept.size() << '\n';
    for (int x : kept) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}
