#include<iostream>
#include<string>

#include "Node.cpp"
#include "DoublyLinkedList.cpp"
#include "LRUCache.cpp"

int main(){

    // LRU cache with capacity 3
    LRUCache<int, std::string> cache(3);

    // insert 3 elements
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");
    // cache:   MRU -> [3][2][1]    <- LRU

    std::cout<<"get(1): "; 
    auto val = cache.get(1);        // MRU -> [1][3][2] <- LRU
    if(val.has_value()) std::cout<<val.value()<<"\n";
    else    std::cout<<"Not found"<<"\n";

    // now size is 3, we add new entry and its overflow so LRU must get evicted
    cache.put(4, "four");

    std::cout<<"get(2): ";
    val = cache.get(2);
    if(val.has_value()) std::cout<<"val.value()\n";
    else    std::cout<<"not found (evicted)\n";

    return 0;
}