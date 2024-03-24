// Reid Luttrell
// File Purpose: Implement the functionality of the Doubly Linked List of Arrays

#include <cstring>
#include <iostream>

#include "list.h"
#include "item.h"

// allocates item array and acts as a wrapper for null_initialize
node::node() : top(0), size(5), next(NULL), prev(NULL) {
    this->items = new Item*[this->size];

    int i = 0;
    this->null_initialize(i);
};

// copy construct a node, acts as a wrapper for copy_items
node::node(const node& from) : top(0), size(DEFAULT_SIZE), next(from.next), prev(from.prev) {
    this->items = new Item*[this->size];

    int i = 0;
    this->null_initialize(i);

    int j = 0;
    this->copy_items(from.items, j);
};

// node destructor acts as wrapper for delete_all
node::~node() {
    int i = 0;
    this->delete_all(i);
    delete[] this->items;
}

// recursively null initialize the items array
void node::null_initialize(int& idx) {
    if (idx >= size) // end of array
        return;

    this->items[idx] = NULL;

    this->null_initialize(++idx);
}

// get the next pointer
node*& node::get_next() {
    return this->next;
}

// get the previous pointer
node*& node::get_prev() {
    return this->prev;
}

// set the next pointer
void node::set_next(node* next) {
    this->next = next;
}

// set the previous pointer
void node::set_prev(node* prev) {
    this->prev = prev;
}

// return whether or not there are items in the array
bool node::is_empty() const {
    return (this->top == 0);
}

// addition wrapper to set up index counter
int node::add(const Item& item) {
    int i = 0; 
    return this->add(item, i);
}

// recursively walk the array, find an empty slot, and load it with a new item based on the RTTI info of the passed item
int node::add(const Item& item, int& idx) {
    if (idx >= this->size) {
        return 0;
    }

    const NewItem* nItem = dynamic_cast<const NewItem*>(&item); // RTTI type checking
    const UsedItem* uItem = dynamic_cast<const UsedItem*>(&item);
    const Electronic* elec = dynamic_cast<const Electronic*>(&item);

    if (!this->items[idx]) { // empty slot, add
        if (nItem) // what kind of item is this based on RTTI data?
            this->items[idx] = new NewItem(*nItem);
        else if (uItem)
            this->items[idx] = new UsedItem(*uItem);
        else if (elec)
            this->items[idx] = new Electronic(*elec);
        else
            return 0;

        ++this->top;
        return 1;
    }

    return this->add(item, ++idx);
}

// removal wrapper to deal with case of no item array
int node::remove(const char* key) {
    if (!this->items)
        return 0;

    int i = 0;
    return this->remove(key, i);
}

// recursively walk the node array and remove the node matching the given key
int node::remove(const char* key, int& idx) {
    if (idx >= this->size) {
        return 0;
    }

    if (this->items[idx]) {
        if (this->items[idx]->compare(key) == 0) {
            delete this->items[idx];
            this->items[idx] = NULL;
            --this->top;

            return 1;
        }
    }

    return this->remove(key, ++idx);
}

// display all wrapper to deal with case of no item array
int node::display_all() const {
    if (!this->items) // list empty
        return 0;

    int idx = 0;
    return this->display_all(idx);
}

// recursively walk the item array and display each node
int node::display_all(int& idx) const {
    if (idx >= this->size) // end of array
        return 1;

    if (this->items[idx]) {
        std::cout << '\n';
        this->items[idx]->display();
    }

    return this->display_all(++idx);
}

// display old wrapper to deal with case of no item array
int node::display_old() const {
    if (!this->items) // list empty
        return 0;

    int idx = this->top - 1; // the index of the top element
    return this->display_old(idx);
}

// reursively walk the array backwards and display the items
int node::display_old(int& idx) const {
    if (idx < 0) // end of array
        return 1;

    if (this->items[idx]) {
        std::cout << '\n';
        this->items[idx]->display();
    }

    return this->display_old(--idx);
}

// display tyep wrapper to deal with case of no item array
int node::display_type(const char* type) const {
    if (!this->items) // no items
        return 0;

    int idx = 0;
    return this->display_type(type, idx);
}

// recursively walk the array and display every item that matches the given type
int node::display_type(const char* type, int& idx) const {
    if (idx >= this->size)
        return 1;

    if (this->items[idx]) {
        if (this->items[idx]->compare_type(type) == 0) { // is this item the right type?
            std::cout << '\n';
            this->items[idx]->display();
        }
    }

    return this->display_type(type, ++idx);
}

// retrieval wrapper to deal with item array being empty case
Item* node::retrieve(const char* key) {
    if (!this->items) // no items
        return NULL;

    int idx = 0;
    return this->retrieve(key, idx);
}

// recursively retrieve item with the given key from the node's array and return it
Item* node::retrieve(const char* key, int& idx) {
    if (idx >= this->size) // not found
        return NULL;

    if (this->items[idx]) {
        if (this->items[idx]->compare(key) == 0) {
            return this->items[idx];
        }
    }

    return this->retrieve(key, ++idx);
}

// delete every item in the node's array
void node::delete_all(int& idx) {
    if (idx >= this->size)
        return;

    if (this->items[idx]) { // may need to remove this check because there could be gaps after removal
        delete this->items[idx];
    }

    this->delete_all(++idx);
}

// recursively copy all the items from the given list into this node object
void node::copy_items(Item** from, int& idx) {
    if (idx >= this->size) {
        return;
    }

    if (from[idx]) {
        this->items[idx] = new Item(*from[idx]); // could be a precedence issue, deref should happen first
        ++this->top;
    }

    this->copy_items(from, ++idx);
}

DoublyLinkedList::DoublyLinkedList() : head(NULL), tail(NULL) {};

// desctructor acts as a wrapper for delete_all
DoublyLinkedList::~DoublyLinkedList() {
    if (!this->head) // empty list
        return;

    this->delete_all(this->head); // implement
}

// copy constructor acts as a wrapper for copy_list
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& from) {
    this->copy_list(this->head, NULL, from.head); // implement this
}

// recursively copy the nodes of a DLL to another DLL
void DoublyLinkedList::copy_list(node*& to, node* prev, node* from) {
    if (!from) { // end of source list
        this->tail = prev; 
        to = NULL;
        return;
    }

    to = new node(*from);

    this->copy_list(to->get_next(), to, from->get_next());
}

// recursively delete every node from the DLL
void DoublyLinkedList::delete_all(node*& head) {
    if (!head) // done
        return;

    node* temp = head; // save
    head = head->get_next(); // adjust
    delete temp; // delete

    this->delete_all(head); // recurse
}

// display wrapper to deal with empty list case
int DoublyLinkedList::display_all() const {
    if (!this->head) // empty list
        return 0;

    return this->display_all(this->head);
}

// recursively walk the DLL and display every item
int DoublyLinkedList::display_all(node* head) const {
    if (!head) // end of list
        return 1;

    std::cout << '\n';
    head->display_all();

    return this->display_all(head->get_next());
}

// display old wrapper to deal with empty list base case
int DoublyLinkedList::display_old() const {
    if (!this->tail) // empty list
        return 0;

    return this->display_old(this->tail);
}

// recursively walk the DLL from tail to head and display the array backwards aswell
int DoublyLinkedList::display_old(node* tail) const {
    if (!tail) // end of list
        return 1;

    std::cout << '\n';
    tail->display_old();

    return this->display_old(tail->get_prev());
}

// display type wrapper to deal with base case of empty list
int DoublyLinkedList::display_type(const char* type) const {
    if (!this->head) // empty list
        return 0;

    return this->display_type(this->head, type);
}

// recursively walk the DLL and display only items of the given type
int DoublyLinkedList::display_type(node* head, const char* type) const {
    if (!head) // end of list
        return 1;

    std::cout << '\n';
    head->display_type(type);

    return this->display_type(head->get_next(), type);
}

DLL::DLL() {}

// copy construct a new DLL from a given one
DLL::DLL(const DLL& from) : DoublyLinkedList(from) {}

/// add a new item to the front of the list
int DLL::add(const Item& to_add) {
    if (!this->head) {
        this->head = new node;
        this->head->set_next(NULL);
        this->head->set_prev(NULL);
        this->tail = this->head; // idk if this is good // modified
    }

    if (!this->head->add(to_add)) { // the array was full, push back and try again
        node* temp = this->head;
        this->head = new node;

        temp->set_prev(this->head);
        this->head->set_next(temp);
        this->head->set_prev(NULL);

        this->head->add(to_add); // this should always work
        return 1;
    }

    return 1;
}

// removal wrapper to deal with list empty base case
int DLL::remove(const char* key) {
    if (!this->head) // list empty
        return 0;

    return this->remove(this->head, key);
}

// recursively walk DLL to find and remove item matching key
int DLL::remove(node*& head, const char* key) {
    if (!head) // not found
        return 0;

    if (head->remove(key)) { // item successfully removed
        if (head->is_empty()) { // check if the removal left the node array empty
            if (head == this->tail) // modified
                this->tail = NULL;

            node* temp = head;
            head = head->get_next();
            delete temp;
        }

        return 1;
    }

    return this->remove(head->get_next(), key);
}

// wrapper to find item in list and return it
Item* DLL::retrieve(const char* key) {
    if (!this->head) // list empty
        return NULL;

    return this->retrieve(this->head, key);
}

// recursively walk DLL to find item matching key and return it
Item* DLL::retrieve(node*& head, const char* key) {
    if (!head) // not found
        return NULL;

    Item* item = head->retrieve(key);
   
    if (item)
        return item;

    return this->retrieve(head->get_next(), key);
}
