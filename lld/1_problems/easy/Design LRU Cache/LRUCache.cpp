#include <unordered_map>
#include <optional>
#include <mutex>

template<typename K, typename V>
class LRUCache{
    private:
        int capacity;
        std::unordered_map<K, Node<K,V>*> map;
        DoublyLinkedList<K,V> list;
        mutable std::mutex mutex;

    public:
        LRUCache(int cap) : capacity(cap) {}
        ~LRUCache(){
            // clean up all nodes stored in map
            for(auto& pair : map){
                delete pair.second;
            }
        }

        std::optional<V> get(const K& key){
            std::lock_guard<std::mutex> lock(mutex);

            auto it = map.find(key);
            if(it == map.end()) return std::nullopt;

            Node<K,V>* node = it->second;
            list.moveToFront(node);     // move node to front
            return node->value;         // return the accessed node
        }

        void put(const K& key, const V& value){
            std::lock_guard<std::mutex> lock(mutex);

            auto it = map.find(key);
            if(it != map.end()){
                // entry aleady exists
                Node<K,V>* node = it->second;
                node->value = value;
                list.moveToFront(node);
            }else{
                // node is new, we need to create a new node
                // check if we have capacity
                if(static_cast<int>(map.size()) == capacity){
                    // need to evict the LRU
                    Node<K,V>* lru = list.removeLast();
                    if(lru != nullptr){ // if we have an entry in the cache
                        map.erase(lru->key);
                        delete lru;
                    }
                }
                // now we have room to add the node entry
                Node<K,V>* newnode = new Node<K,V>(key, value);
                list.addAtFront(newnode);
                map[key] = newnode;
            }
        }
};