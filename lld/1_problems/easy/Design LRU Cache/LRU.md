# LRU Cache
stands for `Least Recently Used`, its type of cache replacement policy that evicts the least recently access item when cache reaches its capacity. in performance critical system caching helps avoid expensive comutations or repeated data fetching, but its limited so when its full, we need a policy to decide `which item to remove`

## Clarifying requirements
```
Q. should the cache support generic K-V pairs or should we restrict it to specific data types ?
=> cache should be generic, should support any type of KV pair as long as Keys are hashable
```
```
Q. should the cache operation be limited to *put()* and *get()* or do we need to support deletions as well ?
=> for now, we can limit operations to the two behaviors
```
```
Q. what should *get()* return if theres no key of requested form found in the cache ?
=> can either return *nullptr* or a sentinel like `1`
```
```
Q. will the cache be used in a multi-threaded environment ? do we need to ensure thread safety ?
=> assume it will be used in multi-threaded server and must be thread-safe
```
```
Q. what are performance expectation for *get()* and *put()* ?
=> both must run in O(1) time on *average*
```

### Summrise the requirements

```
FUNCTIONAL REQUIREMENTS
    - support get(key) operation: return the value if key exists, or return null or -1
    - support put(key, value) opetaion: insert a new k-v pair or update the existing value at the key
    - if cache exceeds its capacity, it should automatically evict the least recently used item
    - both get and put operations should update the recency of accessed/inserted item
    - keys and values should get generic key-value pairs, with keys being hashable
```
```
NON FUNCTIONAL REQUIREMENTS
    - time complexity: both get() and put() should run in O(1)
    - thrad safety : implementation must be thread safe for use in concurrent environment
    - modularity : design should follows OOPs with clear separation of responsibilities
    - memory efficiency: the internal data structures should be optimised for speed and space within the defined constraints.
```
---

## Identify core entities

unlike systems that model real world concepts like users, products or bookings, LRU cache is centred around choosing right data structure and itnernal abstractions to acheieve required functionality and performance
```
- we need *fast key-based lookup for each reads and updates
- we need *fast orering* to track item usage and enfore eviction based on recency
```

1. we need get and put to be O(1) so naturally we incline towards `HASHMAP`, but the issue is hashmap doesnt maintain order, it cant tell us which entry was accessed least recently. 
2. also we need to maintain recency, `move recently accessed item to front`, `remove least recently from the back of cache when capacity exceeds` and `insert new item in from` all in `O(1)` time. thus we naturall incline to `Double linked list` as it maintains reference to both `prev` and `next` nodes, thus we can remove a node if we have a reference to it in O(1), move a node to the head in O(1) and remove LRU node from tail in O(1)

so when we combine both the structures

```yaml
         _____INPUT_____         ___OPS_____         ____LRU CACHE SYSTEM_________________________
        |               |       |           |       |   ______________                            |
        |   ________    |-------|->[ get ]  |-------|->|              |                           |
        |  | client |   |       |           |-------|->|    HASHMAP   |<--->[Doubly Linked List]  |
        |  |________|   |-------|->[ put ]  |       |  |______________|                           |
        |_______________|       |___________|       |_____________________________________________|

- hashmap provides O(1) lookip, instead of storing the values directly, it stores pointer/reference to node in DLL
- DLL maintains usage order, head is always MRU and tail is always LRU item
```

beyon `Hashmap` and `DLL` we need two more classes to encapsulate and organise out logic:
1. NODE: simple internal class representing an individual entry in cache and a node in linked list. it stores k-v pair and maintains pointers to adjacent nodes.
2. LRUCache: the main class that exposes public cache API and coordinates all opetaions. it owns both `hashmap` and the `DLL`

## Class Definition

we will work bottom up, simple types first, then classes with real logic, this makes sense as complex systems depends on simpler ones.

### Node<K,V>
the node represents an individual entry in the cache and serves as a node in DLL
```yaml  ___________________________
        |       Node<k,v>           |
        |___________________________|
        |   -K key                  |
        |   -V value                |
        |   -Node<k,v> prev         |
        |   -Node<k,v> next         |
        |___________________________|
        |   +Node(K key, V value)   |
        |___________________________|
```
`Node(key, value)` is the constructor that initializes key and value. the node class is intentionally simple. its data container with minimal behavior, both `prev` and `next` are mutable as the position in the list changes as items are accessed.

### DoublyLinkedList<K,V>
utility that manages the MRU and LRU ordering of cache entries.
```yaml

        _____________________________
       |    DoublyLinkedList<K,V>    |
       |_____________________________|
       | - Node<k,v> head            |     _________________
       | - Node<k,v> tail            |    |  Node<k,v>      |
       |_____________________________|<.>-|_________________|
       | +DoubleLinkedlList()        |    | -K key          |
       | +addFirst(Node<k,v> node)   |    | -V value        |
       | +remove(Node<k,v> noed)     |    | -Node<k,v> prev |
       | +moveToFront(Node<k,v> node)|    | -Node<k,v> next |
       | +removeLast() : Node<k,v>   |    |_________________|
       |_____________________________|    |_________________|
```
`DESIGN DECISION` : use dummy head and tail nodes so that we can manage `addition to empty list`, `removal of only node` and `removing first and last node`. dummy node elimiantes all such edge cases. this enables that all real nodes has a valid `prev` and `next` pointer.
```yaml
[dummy head] <-> [first node] <-> [next node] <-> [dummy tail]
```

### LRUCache<K,V>
the main class that provies the public APIs get() and put() and manages overall cache logic

```yaml  _____________________________                      _____________________________
        |   LRUCache<K,V>             |                    |    DoublyLinkedList<K,V>    |
        |_____________________________|                    |_____________________________|
        | -int capacity               |        OWNS        | -Node<K,V> head             |
        | -Map<K, Node<k,v>> map      |<.>-----------------| -Node<K,V> tail             |
        | -DoublyLinkedLisy<k,v> list |                    |_____________________________|
        |_____________________________|                    |_____________________________|
        | +LRUCache(int capacity)     |                                 <.> contains
        | +get(int k) : V             |                     _____________|______________
        | +put(K key, V value)        |                    |        Node<K,V>           |
        |_____________________________|                    |____________________________|
                               |                           | -K key                     |
                               |                           | -V value                   |
                               |_____creates/uses_________>|____________________________|
                                                           |____________________________|








