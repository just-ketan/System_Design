template <typename K, typename V>
// struct defualts to public access, for data containers like Node, it simpler to use a struct instead of class
struct Node{
    K key;
    V value;
    Node *prev, *next;
    Node(K k, V v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};