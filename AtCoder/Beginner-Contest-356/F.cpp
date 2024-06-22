#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>
#include <utility>

template<typename T, typename Compare = std::less<T>>
class IndexedSet {

    enum class Color { RED, BLACK };

    struct Node {
        T val;
        Color color;
        int subtree_size;
        Node *left, *right, *parent;
        Node(T v) : val{ v }, color{ Color::RED }, subtree_size{ 1 } {
            setRefs(nullptr, nullptr, nullptr);
        }
        template<typename... Args>
        Node(Args&&... args) : val{ std::forward<Args>(args)... },
        color{ Color::RED }, subtree_size{ 1 } {
            setRefs(nullptr, nullptr, nullptr);
        }
        ~Node() { delete left; delete right; }
        void setRefs(Node* p, Node* l, Node* r) { parent = p; left = l; right = r; }
        void setSubtreeSize() {
            subtree_size = 1 + (right ? right->subtree_size : 0) + (left ? left->subtree_size : 0);
        }
    };

    static bool isBlack(const Node* n) { return !n || n->color == Color::BLACK; }
    static bool isRed(const Node* n) { return n && n->color == Color::RED; }
    static void setRed(Node* n) { n->color = Color::RED; }
    static void setBlack(Node* n) { n->color = Color::BLACK; }

    class Iterator {
        const IndexedSet* iset;
        Node* node;
        friend class IndexedSet;
    public:
        Iterator(const IndexedSet* s, Node* n) : iset{ s }, node{ n } {}
        Iterator(const Iterator& itr) : iset{ itr.iset }, node{ itr.node } {}
        const Iterator& operator++() {
            assert(node != nullptr); node = next(node); return *this;
        }
        const Iterator& operator--() {
            assert(node != iset->first_elem); node = prev(node); return *this;
        }
        const Iterator operator++(int) {
            assert(node != nullptr); Iterator t = *this; node = next(node); return t;
        }
        const Iterator operator--(int) {
            assert(node != iset->first_elem); Iterator t = *this; node = prev(node); return t;
        }
        const Iterator operator+(int x) {
            Iterator itr = Iterator(*this);
            while (x--) ++itr;
            return itr;
        }
        const Iterator operator-(int x) {
            Iterator itr = Iterator(*this);
            while (x--) --itr;
            return itr;
        }
        bool operator==(const Iterator& o) const { return node == o.node; }
        bool operator!=(const Iterator& o) const { return node != o.node; }
        T operator*() const { assert(node); return node->val; }
        const T* operator->() const { return &node->val; }
    private:
        Node* next(Node* cur) const {
            return cur == iset->last_elem ? nullptr : iset->next(cur);
        }
        Node* prev(Node* cur) const {
            return cur == nullptr ? iset->last_elem : iset->prev(cur);
        }
    };

    Node *root, *first_elem, *last_elem;
    int tree_size;
    Compare less;
    Iterator end_itr = Iterator(this, nullptr);

public:
    IndexedSet() : tree_size{ 0 } { root = first_elem = last_elem = nullptr; }
    IndexedSet(const IndexedSet& iset) : IndexedSet() { *this = iset; }
    IndexedSet(const std::initializer_list<T>& ilist) : IndexedSet() {
        for (const auto& val : ilist) insert(val);
    }
    ~IndexedSet() { clear(); }

    IndexedSet& operator=(const IndexedSet& iset) {
        clear();
        for (const auto& val : iset) insert(val);
        return *this;
    }
    
    void clear() {
        delete root;
        root = first_elem = last_elem = nullptr;
        tree_size = 0;
    }

    Iterator begin() const { return Iterator(this, first_elem); }
    Iterator end() const { return end_itr; }
    Iterator last() const { return Iterator(this, last_elem); }
    int size() const { return tree_size; }
    bool empty() const { return tree_size == 0; }
    bool contains(const T& key) { return find(key) != end_itr; }

    T& operator[](int i) {
        assert(i >= 0 && i < tree_size);
        Node* cur = root;
        int num_less = 0;
        while (cur != nullptr) {
            int num_left = cur->left ? cur->left->subtree_size : 0;
            if (num_less + num_left > i) {
                cur = cur->left;
            } else if (num_less + num_left < i) {
                num_less += 1 + num_left;
                cur = cur->right;
            } else
                return cur->val;
        }
        std::exit(-1);
    }

    std::pair<Iterator, bool> insert(const T& key) {
        return addNode(new Node(key));
    }

    template<typename... Args>
    std::pair<Iterator, bool> emplace(Args&&... args) {
        return addNode(new Node(std::forward<Args>(args)...));
    }

    int erase(const T& key) {
        Node* cur = root;
        while (cur != nullptr) {
            if (less(key, cur->val))
                cur = cur->left;
            else if (less(cur->val, key))
                cur = cur->right;
            else
                break;
        }
        if (cur == nullptr)
            return 0;
        deleteNode(cur);
        return 1;
    }

    Iterator erase(const Iterator& pos) {
        assert(pos != end_itr);
        Node* cur = pos.node;
        if (pos == end_itr)
            return end_itr;
        Iterator next_elem = cur == last_elem ? end_itr : Iterator(this, next(cur));
        deleteNode(cur);
        return next_elem;
    }

    Iterator find(const T& key) {
        Node* cur = root;
        while (cur != nullptr) {
            if (less(key, cur->val))
                cur = cur->left;
            else if (less(cur->val, key))
                cur = cur->right;
            else
                return Iterator(this, cur);
        }
        return end_itr;
    }

    Iterator lower_bound(const T& key) const {
        Node* cur = root;
        Node* result = nullptr;
        while (cur != nullptr) {
            if (less(cur->val, key))
                cur = cur->right;
            else {
                result = cur;
                cur = cur->left;
            }
        }
        return Iterator(this, result);
    }

    Iterator upper_bound(const T& key) {
        Node* cur = root;
        Node* result = nullptr;
        while (cur != nullptr) {
            if (less(key, cur->val)) {
                result = cur;
                cur = cur->left;
            } else
                cur = cur->right;
        }
        return Iterator(this, result);
    }

    int count_less(const T& key) {
        Node* cur = root;
        int res = 0;
        while (cur != nullptr) {
            if (less(cur->val, key)) {
                res += 1 + (cur->left ? cur->left->subtree_size : 0);
                cur = cur->right;
            } else
                cur = cur->left;
        }
        return res;
    }

    int count_greater(const T& key) {
        Node* cur = root;
        int res = 0;
        while (cur != nullptr) {
            if (less(key, cur->val)) {
                res += 1 + (cur->right ? cur->right->subtree_size : 0);
                cur = cur->left;
            } else
                cur = cur->right;
        }
        return res;
    }

    void printTree() const {
        std::cout << "-------- RB TREE: size: " << tree_size << " ------------------------\n";
        printTreeRec(root, 0);
        std::cout << "root: " << (root == nullptr ? 0 : root->val) << ' ' << root << '\n';
        std::cout << "first_elem: " << (first_elem == nullptr ? 0 : first_elem->val) << ' ' << first_elem << '\n';
        std::cout << "last_elem: " << (last_elem == nullptr ? 0 : last_elem->val) << ' ' << first_elem << '\n';
        std::cout << "------------------------------------------------------------\n";
    }

private:

    void printTreeRec(const Node* cur, int space) const {
        if (cur == nullptr) return;
        printTreeRec(cur->right, space + 6);
        std::string str(space, ' ');
        std::cout << str << ' ' << cur->val << '(' << (isRed(cur) ? 'R' : 'B') << ')' << '(' << cur << ')' << '\n';
        printTreeRec(cur->left, space + 6);
    }

    Node* next(Node* cur) const {
        if (cur->right != nullptr) {
            cur = cur->right;
            while (cur->left != nullptr) cur = cur->left;
            return cur;
        }
        while (cur->parent->right == cur) cur = cur->parent;
        return cur->parent;
    }

    Node* prev(Node* cur) const {
        if (cur->left != nullptr) {
            cur = cur->left;
            while (cur->right != nullptr) cur = cur->right;
            return cur;
        }
        while (cur->parent->left == cur) cur = cur->parent;
        return cur->parent;
    }

    std::pair<Iterator, bool> addNode(Node* new_node) {
        if (root == nullptr) {
            root = first_elem = last_elem = new_node;
            setBlack(root);
            tree_size = 1;
            return { Iterator(this, new_node), true };
        }
        Node* cur = root;
        while (true) {
            if (less(new_node->val, cur->val)) {
                if (cur->left == nullptr) {
                    cur->left = new_node;
                    break;
                }
                cur = cur->left;
            }
            else if (less(cur->val, new_node->val)) {
                if (cur->right == nullptr) {
                    cur->right = new_node;
                    break;
                }
                cur = cur->right;
            }
            else {
                delete new_node;
                return { Iterator(this, cur), false };
            }
        }
        new_node->parent = cur;
        ++tree_size;
        do {
            ++cur->subtree_size;
            cur = cur->parent;
        } while (cur != nullptr);
        if (less(new_node->val, first_elem->val))
            first_elem = new_node;
        if (less(last_elem->val, new_node->val))
            last_elem = new_node;
        rebalance(new_node);
        return { Iterator(this, new_node), true };
    }

    void transplant(Node* a, Node* b) {
        if (root == a) root = b;
        else if (root == b) root = a;
        if (first_elem == a) first_elem = b;
        else if (first_elem == b) first_elem = a;
        if (last_elem == a) last_elem = b;
        else if (last_elem == b) last_elem = a;
        std::swap(b->color, a->color);
        std::swap(b->subtree_size, a->subtree_size);
        Node* bp = b->parent;
        Node* ap = a->parent;
        std::swap(a->parent, b->parent);
        if (bp != nullptr) (bp->left == b ? bp->left : bp->right) = a;
        if (ap != nullptr) (ap->left == a ? ap->left : ap->right) = b;
        if (b->left) b->left->parent = a;
        if (a->left) a->left->parent = b;
        std::swap(a->left, b->left);
        if (b->right) b->right->parent = a;
        if (a->right) a->right->parent = b;
        std::swap(a->right, b->right);
    }

    void deleteNode(Node* cur) {
        --tree_size;
        if (cur->left != nullptr && cur->right != nullptr) {
            Node* minRight = cur->right;
            while (minRight->left != nullptr) minRight = minRight->left;
            transplant(minRight, cur);
        }
        if (cur->left != nullptr) transplant(cur->left, cur);
        else if (cur->right != nullptr) transplant(cur->right, cur);
        if (tree_size != 0) {
            if (first_elem == cur) first_elem = next(first_elem);
            if (last_elem == cur) last_elem = prev(last_elem);
        }
        if (isBlack(cur)) fixDoubleBlack(cur);
        Node* p = cur->parent;
        if (p != nullptr) {
            (p->left == cur ? p->left : p->right) = nullptr;
            do { --p->subtree_size; p = p->parent; } while (p != nullptr);
        }
        delete cur;
        if (tree_size == 0) first_elem = last_elem = root = nullptr;
    }

    void fixDoubleBlack(Node* cur) {
        if (cur->parent == nullptr) return;
        Node* p = cur->parent;
        bool leftDB = p->left == cur;
        Node* s = leftDB ? p->right : p->left;
        if (isRed(s)) {
            std::swap(p->color, s->color);
            if (leftDB) rotateLeft(p);
            else rotateRight(p);
            fixDoubleBlack(cur);
            return;
        }
        Node* sl = s->left;
        Node* sr = s->right;
        if (isBlack(sl) && isBlack(sr)) {
            setRed(s);
            if (isRed(p)) setBlack(p);
            else fixDoubleBlack(p);
            return;
        }
        if (leftDB) {
            if (isRed(sr)) {
                std::swap(p->color, s->color);
                rotateLeft(p);
                setBlack(sr);
            } else {
                std::swap(s->color, sl->color);
                rotateRight(s);
                fixDoubleBlack(cur);
            }
        } else {
            if (isRed(sl)) {
                std::swap(p->color, s->color);
                rotateRight(p);
                setBlack(sl);
            }
            else {
                std::swap(s->color, sr->color);
                rotateLeft(s);
                fixDoubleBlack(cur);
            }
        }
    }

    void rebalance(Node* cur) {
        if (cur == root) { setBlack(cur); return; }
        if (isBlack(cur) || isBlack(cur->parent)) return;
        Node* p = cur->parent;
        Node* g = p->parent;
        Node* u = g->left == p ? g->right : g->left;
        if (isRed(u)) {
            setRed(g); setBlack(p); setBlack(u);
            rebalance(g);
            return;
        }
        bool r1 = g->right == p, r2 = p->right == cur;
        if (r1 == r2) {
            if (r1) rotateLeft(g);
            else rotateRight(g);
            setBlack(p);
        }
        else {
            if (r1) {
                rotateRight(p);
                rotateLeft(g);
            } else {
                rotateLeft(p);
                rotateRight(g);
            }
            setBlack(cur);
        }
        setRed(g);
    }

    void rotateLeft(Node* x) {
        Node *r = x->right, *p = x->parent, *c = x->right->left;
        x->setRefs(r, x->left, c);
        r->setRefs(p, x, r->right);
        if (c != nullptr) c->parent = x;
        if (p != nullptr) (p->right == x ? p->right : p->left) = r;
        else root = r;
        x->setSubtreeSize();
        r->setSubtreeSize();
    }

    void rotateRight(Node* x) {
        Node *l = x->left, *p = x->parent, *c = x->left->right;
        x->setRefs(l, c, x->right);
        l->setRefs(p, l->left, x);
        if (c != nullptr) c->parent = x;
        if (p != nullptr) (p->right == x ? p->right : p->left) = l;
        else root = l;
        x->setSubtreeSize();
        l->setSubtreeSize();
    }
};

struct Component {
    long long l, r, size;

    Component(long long l, long long r, long long s) : l{ l }, r{ r }, size{ s } {}

    Component(long long x) {
        l = r = x;
        size = 1;
    }

    void add(long long x) {
        ++size;
        if (x < l) l = x;
        if (x > r) r = x;
    }

    bool operator<(const Component& o) const {
        return r < o.l;
    }
};

const long long INF = 3e18;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long q, k;
    std::cin >> q >> k;
    IndexedSet<long long> nums = { -INF, INF };
    IndexedSet<Component> comps = { { -INF }, { INF } };
    for (int i = 0; i < q; ++i) {
        long long t, x;
        std::cin >> t >> x;
        if (t == 2) {
            std::cout << comps.find(Component(x))->size << '\n';
            continue;
        }
        auto ni = nums.find(x);
        if (ni == nums.end()) {
            Component cur = Component(x);
            auto ci = comps.find(cur);
            if (ci == comps.end()) {
                auto prev = --comps.lower_bound(cur);
                auto next = prev + 1;
                if (cur.l - prev->r <= k) {
                    cur = { prev->l, cur.r, cur.size + prev->size };
                    comps.erase(prev);
                }
                if (next->l - cur.r <= k) {
                    cur = { cur.l, next->r, cur.size + next->size };
                    comps.erase(next);
                }
            }
            else {
                cur = *ci;
                comps.erase(ci);
                cur.add(x);
            }
            comps.insert(cur);
            nums.insert(x);
            continue;
        }
        auto comp_itr = comps.find(Component(x));
        Component cur = *comp_itr;
        comps.erase(comp_itr);
        if (cur.size > 1) {
            auto next = ni + 1;
            auto prev = ni - 1;
            --cur.size;
            if (cur.l == x)      cur.l = *next;  
            else if (cur.r == x) cur.r = *prev;
            else if (*next - *prev > k) {
                long long leftCount = nums.count_less(x) - nums.count_less(cur.l);
                comps.emplace(*next, cur.r, cur.size - leftCount);
                cur = { cur.l, *prev, leftCount };
            }
            comps.insert(cur);
        }
        nums.erase(ni);
    }
}
