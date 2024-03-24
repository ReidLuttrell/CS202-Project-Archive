// Reid Luttrell
// File Purpose : encapsulate and provide prototyping for the doubly linked list of arrays

class Item;

// the default size of the item array
const int DEFAULT_SIZE = 5;

// class node contains the array of items
// and provides display and modification of said data
class node {
public:
    // default construct the data members
    node();
    // copy construct a node from another node
    node(const node& from);
    // delete all dynamic data held in item array
    ~node();

    // set the default value of all item array indices to null
    void null_initialize(int& idx); 

    // return the next pointer
    node*& get_next();
    // return the previous pointer
    node*& get_prev();
    // set the next pointer to given node
    void set_next(node* next);
    // set previous pointer to given node
    void set_prev(node* prev);

    bool is_empty() const;
    // wrapper to add a new item to the array
    // returns success
    int add(const Item& item);
    // wrapper to remove an item from the array
    // return success
    int remove(const char* key);
    // wrapper to display all the items in the item array
    // return success
    int display_all() const;
    // wrapper to display all the items in the array backwards
    // return success
    int display_old() const;
    // wrapper to display all items of the given type
    // return success
    int display_type(const char* type) const;
    // wrapper to find item with key
    // return pointer to found item or NULL
    Item* retrieve(const char* key);
protected:
    // recursively add a new item to the array
    // returns success
    int add(const Item& item, int& idx);
    // recursively walk array and remove item with key
    // return success
    int remove(const char* key, int& idx);
    // recursively walk itemm array and display each item
    // return success
    int display_all(int& idx) const;
    // recursively walk item array backwards and display each item
    // return success
    int display_old(int& idx) const;
    // recursively walk the array and display all items of the given type
    // return success
    int display_type(const char* type, int& idx) const;
    // recursivey walk array and find item with given name
    // return pointer to found item or NULL
    Item* retrieve(const char* key, int& idx);

    // recursively walk array and delete all nodes
    void delete_all(int& idx);
    // copy given item array into this object
    void copy_items(Item** from, int& idx);

    // used to check if array is empty
    int top;
    // the max size of the array defaulted to 5
    int size;
    // the array of item pointers
    Item** items; // double pointer to check for validity

    // pointer to the next node
    node* next;
    // pointer to the previous node
    node* prev;    
};

// class doublylinkedlist contains the head of the doubly linked list
// and proides display and modification of the list
class DoublyLinkedList { // doubly linked list of arrays
public:
    // default construct the doubly linked list
    DoublyLinkedList();
    // copy construct the doubly linked list given the list to copy
    DoublyLinkedList(const DoublyLinkedList& other);
    // delete the entire list
    ~DoublyLinkedList();

    // wrapper to display each node's data
    // return success
    int display_all() const;
    // wrapper to display each node's data going backwards
    // return success
    int display_old() const;
    // wrapper to display each node of the given type's data
    // return success
    int display_type(const char* key) const;
protected:
    // recursively walk the list and display each item array
    // return success
    int display_all(node* head) const;
    // recursively walk the list backwards and display each item backwards
    // return success
    int display_old(node* tail) const;
    // recursively walk the list and display each item of the given type
    // return success
    int display_type(node* head, const char* type) const;
    // recursively copy each node from the list
    void copy_list(node*& to, node* prev, node* from);
    // recursively delete every node from the list
    void delete_all(node*& head);

    // pointer to the head of the list
    node* head;
    // pointer to the tail of the list
    node* tail;
};

// class DLL encapsulates is a doubly linked list with
// the functionality that treats it as such
class DLL : public DoublyLinkedList {
public:
    // default construct the DLL
    DLL();
    // copy construct the DLL with the given DLLL
    DLL(const DLL& from);

    // add a new item to the array at the head of the DLL
    int add(const Item& from);
    // wrapper to remove an item from a node's array given the key
    int remove(const char* key);
    // wrapper to retrieve an item from the list
    // returns pointer to found item or NULL
    Item* retrieve(const char* key);
protected:
    // recursively walk the nodes and remove the item with the key from the array
    int remove(node*& head, const char* key);
    // recursively retrieve the item with the given key name
    // returns pointer to found item or NULL
    Item* retrieve(node*& head, const char* key);
};
