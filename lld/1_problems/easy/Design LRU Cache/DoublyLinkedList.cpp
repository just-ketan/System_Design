// Doubly Linked List class
template<typename K, typename V>
class DoublyLinkedList{
    private:
        Node<K,V> *head, *tail;
    
    public:
        DoublyLinkedList(){
            head = new Node<K,V>(K{}, V{});
            tail = new Node<K,V>(K{}, V{});

            head->next = tail;
            tail->prev = head;
        }

        ~DoublyLinkedList(){
            // delete dummy, real nodes are managed by LRUCache class
            delete head;
            delete tail;
        }

        void addAtFront(Node<K,V>* node){
            // first, make links for node to be between head and first node (head->next)
            node->next = head->next;
            node->prev = head;
            // second, modify the head->next and hest->next->prev links 
            head->next->prev = node;
            head->next = node;
        }

        void remove(Node<K,V>* node){
            // bypass node by linking prev and next
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        void moveToFront(Node<K,V>* node){
            remove(node);
            addAtFront(node);
        }

        Node<K,V>* removeLast(){
            if(tail->prev == head){ return nullptr; }   // no nodes in the list
            Node<K,V>* last = tail->prev;
            remove(last);
            return last;
        }
};