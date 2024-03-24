// Reid Luttrell
// File Purpose: implement list functionality

#include <iostream>
#include <cstring>
#include "list.h"

// null initialize data
Activity::Activity() : name(NULL), desc(NULL) {}

// delete dynamic information
Activity::~Activity() {
    delete[] this->name;
    delete[] this->desc;
}

// deep copy data from given parameters into this object
Activity::Activity(const char* name, const char* desc) {
    int nameLen = std::strlen(name);
    this->name = new char[nameLen + 1];
    std::strcpy(this->name, name);
    this->name[nameLen] = '\0';

    int descLen = std::strlen(desc);
    this->desc = new char[descLen + 1];
    std::strcpy(this->desc, desc);
    this->desc[descLen] = '\0';
}

// deep copy data from given object into this object
Activity::Activity(const Activity& from) {
    int nameLen = std::strlen(from.name);
    this->name = new char[nameLen + 1];
    std::strcpy(this->name, from.name);
    this->name[nameLen] = '\0';

    int descLen = std::strlen(from.desc);
    this->desc = new char[descLen + 1];
    std::strcpy(this->desc, from.desc);
    this->desc[descLen] = '\0';
}

// deep copy data from given object into this object
Activity& Activity::operator=(const Activity& from) {
    int nameLen = std::strlen(from.name);
    this->name = new char[nameLen + 1];
    std::strcpy(this->name, from.name);
    this->name[nameLen] = '\0';

    int descLen = std::strlen(from.desc);
    this->desc = new char[descLen + 1];
    std::strcpy(this->desc, from.desc);
    this->desc[descLen] = '\0';

    return *this;
}

// checks if the name of this object is equal to given object
bool Activity::operator==(const Activity& other) const {
    return this->compare(other) == 0;
}

// checks if the name of this object is equal to the given name
bool Activity::operator==(const char* key) const {
    return this->compare(key) == 0;
}

// checks if the name of this object isn't equal to given object
bool Activity::operator!=(const Activity& other) const {
    return this->compare(other) != 0;
}

// checks if the name of this object isn't equal to given name
bool Activity::operator!=(const char* key) const {
    return this->compare(key) != 0;
}

// compare name of this object to given name
int Activity::compare(const char* key) const {
    return std::strcmp(this->name, key);
}

// compare name of this object to given object
int Activity::compare(const Activity& to) const {
    return std::strcmp(this->name, to.name);
}

// add price onto total, this one doesnt contain price so does nothing
void Activity::add_total(int& total) const {}

// display this object's data
void Activity::display() const {
    std::cout << "Name: " << this->name << '\n';
    std::cout << "Description: " << this->desc << "\n";
}

// deep copy data from client into this object
void Activity::read() {
    char name[MAX_BYTE];
    char desc[MAX_BYTE];

    std::cout << "Enter the name of the Activity: ";
    std::cin.get(name, MAX_BYTE, '\n');
    std::cin.ignore(BIG_NUMBER, '\n');

    std::cout << "Enter a description of the Activity: ";
    std::cin.get(desc, MAX_BYTE, '\n');
    std::cin.ignore(BIG_NUMBER, '\n');

    *this = Activity(name, desc);
}

// null initialize dynamic origin member
Coffee::Coffee() : origin(NULL) {}

// delete dynamic data
Coffee::~Coffee() {
    delete[] this->origin;
}

// deep copy given coffee object into this object
Coffee::Coffee(const Coffee& from) : Activity(from), price(from.price) {
    int originLen = std::strlen(from.origin);
    this->origin = new char[originLen + 1];
    std::strcpy(this->origin, from.origin);
    this->origin[originLen] = '\0';
}

// add price onto total
void Coffee::add_total(int& total) const {
    total += this->price;
}

// display this object's data
void Coffee::display() const {
    std::cout << "Coffee: \n";
    Activity::display();

    std::cout << "Origin: " << this->origin << '\n';
    std::cout << "Price: " << this->price << "\n\n";
}

// deep copy data from client into this object
void Coffee::read() {
    Activity::read();

    char origin_name[MAX_BYTE];
    std::cout << "What is the origin of the coffee?: ";
    std::cin.get(origin_name, MAX_BYTE, '\n');
    std::cin.ignore(BIG_NUMBER, '\n');

    int originLen = std::strlen(origin_name);
    this->origin = new char[originLen + 1];
    std::strcpy(this->origin, origin_name);
    this->origin[originLen] = '\0';

    int price;
    std::cout << "What is the price of this activity?: ";
    std::cin >> price;
    std::cin.ignore(BIG_NUMBER, '\n');

    this->price = price;
}

// null initialize dynamic type member
Game::Game() : type(NULL) {}

// delete dynamic data
Game::~Game() {
    delete[] this->type;
}

// deep copy given game object data into this object
Game::Game(const Game& from) : Activity(from) {
    int typeLen = std::strlen(from.type);
    this->type = new char[typeLen + 1];
    std::strcpy(this->type, from.type);
    this->type[typeLen] = '\0';
}

// display this object's data
void Game::display() const {
    std::cout << "Game: \n";
    Activity::display();

    std::cout << "Type: " << this->type << '\n';
    std::cout << "Price: free!\n\n";
}

// deep copy data from client into this object
void Game::read() {
    Activity::read();

    char type_name[MAX_BYTE];
    std::cout << "What is the type of the game?: ";
    std::cin.get(type_name, MAX_BYTE, '\n');
    std::cin.ignore(BIG_NUMBER, '\n');

    int typeLen = std::strlen(type_name);
    this->type = new char[typeLen + 1];
    std::strcpy(this->type, type_name);
    this->type[typeLen] = '\0';
}

// default constructor - no dynamic data
Bakery::Bakery() {}

// deep copy given bakery object's data into this object
Bakery::Bakery(const Bakery& from) : Activity(from), price(from.price) {}

// add price onto total
void Bakery::add_total(int& total) const {
    total += this->price;
}

// display this object's data
void Bakery::display() const {
    std::cout << "Baked Good: \n";
    Activity::display();

    std::cout << "Price: " << this->price << "\n\n";
}

// deep copy data from client into this object
void Bakery::read() {
    Activity::read();

    int price;
    std::cout << "What is the price of this activity?: ";
    std::cin >> price;
    std::cin.ignore(BIG_NUMBER, '\n');

    this->price = price;
}

// null inititalize Node object and underlying activity object
Node::Node() : activity(NULL), next(NULL) {};

// delete dynamic data
Node::~Node() {
    delete this->activity;
}

// null inititalize node object data and pass existing activity object data into this object's activity constructor
Node::Node(const Activity& from) : next(NULL) {
    const Coffee* coffee = dynamic_cast<const Coffee*>(&from);
    const Game* game = dynamic_cast<const Game*>(&from);
    const Bakery* bakery = dynamic_cast<const Bakery*>(&from);

    if (coffee) { 
        this->activity = new Coffee(*coffee); // allocate memory and construct
    } else if (game)
        this->activity = new Game(*game);
    else if (bakery) {
        this->activity = new Bakery(*bakery);
    }
};

// null inititalize node and copy activity data from existing node into this node's activity object
Node::Node(const Node& from) : activity(NULL), next(from.next) {}

// wrapper to compare underlying activity name to key
int Node::compare(const char* key) {
    return this->activity->compare(key);
}

// wrapper to compare underlying activity to other name
int Node::compare(const Activity& other) {
    return this->activity->compare(other);
}

// return activity member
Activity*& Node::get_activity() {
    return this->activity;
}

// return the next pointer
Node*& Node::get_next() {
    return this->next;
}

// set the next pointer
void Node::set_next(Node* next) {
    this->next = next;
};

// null initialize members
LinkedList::LinkedList() : head(NULL) {};

// delete all dynamic memory in the list, acts as a wrapper for delete_all
LinkedList::~LinkedList() {
    if (!this->head)
        return;

    this->delete_all(head);
}

// copy the given list into this object, acts as a wrapper for copy_list
LinkedList::LinkedList(const LinkedList& from) {
    this->copy_list(this->head, from.head);
}

// compare the name of the head of the list to the name of this one
int LinkedList::compare_head(const char* key) {
    return this->head->compare(key);
}

// compare the name of the head of the list to the name of this one
int LinkedList::compare_head(const Activity& activity) {
    return this->head->compare(activity);
}

// wrapper to copy list to this one
void LinkedList::copy_list(const LinkedList& from) {
    this->delete_all(this->head);

    this->copy_list(this->head, from.head);
}

// recursively copy the list used by the copy constructor
void LinkedList::copy_list(Node*& to, Node* from) {
    if (!from) { // empty source, empty dest
        to = NULL;
        return;
    }

    to = new Node(*from); // allocate space while constructing new node

    this->copy_list(to->get_next(), from->get_next()); // recurse
}

// recursively delete all nodes from the list
void LinkedList::delete_all(Node*& head) {
    if (!head)
        return;

    Node* temp = head; // save
    head = head->get_next(); // adjust
    delete temp; // delete

    this->delete_all(head);
}

// wrapper to deal with base cases for displaying list
void LinkedList::display_all() const {
    if(!this->head)
        return;

    std::cout << "Node:\n\n";
    this->display_all(this->head);
}

// recursively traverse list and display each node
void LinkedList::display_all(Node* head) const {
    if(!head)
        return;

    head->get_activity()->display(); // display the message

    this->display_all(head->get_next());
}

// default does nothing because this object itself has no data
LLL::LLL() {}

// copy constructor just calls LinkedList's copy constructor because it has the data
LLL::LLL(const LLL& from) : LinkedList(from) {};

// deep copy linked list into this one
LLL& LLL::operator=(const LLL& other) {
    this->delete_all(this->head);
    this->copy_list(other);
    return *this;
}

// append a linked list onto this one
LLL LLL::operator+(const LLL& other) {
    LLL list(*this);
    list.append_list(other.head);
    return list;
}

// add a node to this list
LLL LLL::operator+(const Activity& to_add) {
    LLL list(*this);
    list.add(to_add);
    return list;
}

// append a linked list onto this one
LLL& LLL::operator+=(const LLL& other) {
    this->append_list(other.head);
    return *this;
}

// add a new node to the list
LLL& LLL::operator+=(const Activity& to_add) {
    this->add(to_add);
    return *this;
}

// display the linked list
std::ostream& operator<<(std::ostream& out, const LLL& list) {
    list.display_all();
    return out;
}

// check if equal
bool LLL::operator==(const LLL& other) const {
    return this->is_equal(this->head, other.head);
}

// check if not equal
bool LLL::operator!=(const LLL& other) const {
    return !this->is_equal(this->head, other.head);
}

// returns whether or not this list has more nodes than given list
bool LLL::operator>(const LLL& other) const {
    return this->has_more(this->head, other.head);
}

// returns whether or not this list has less nodes than given list
bool LLL::operator<(const LLL& other) const {
    return this->has_more(other.head, this->head);
}

// returns whether or not this list has more or equal nodes to given list
bool LLL::operator>=(const LLL& other) const {
    return this->has_more(this->head, other.head) || this->is_equal(this->head, other.head);
}

// returns whether or not this list has less or equal nodes to given list
bool LLL::operator<=(const LLL& other) const {
    return this->has_more(other.head, this->head) || this->is_equal(this->head, other.head);
}

// retrieve based on key
Activity* LLL::operator[](const char* key) { // maybe const, but im returning a reference to memory so probably can't be const
    return this->retrieve(key);
}

// returns whether or not the list is empty
bool LLL::is_empty() const {
    return !this->head;
}

// wrapper to add a new node to the underlinked linkedlist
int LLL::add(const Activity& to_add) {
    return this->add(this->head, to_add);
}

// recursively traverse to the end of the list and add the new node
int LLL::add(Node*& head, const Activity& to_add) {
    if (!head) {
        head = new Node(to_add);
        return 1;
    }

    this->add(head->get_next(), to_add);
    return 0;
}

// wrapper to deal with base cases in removing node from list
int LLL::remove(const char* key) {
    if (!this->head)
        return 0;

    return this->remove(this->head, key);
}

// recursively traverse list and remove node that matachces key
int LLL::remove(Node*& head, const char* key) {
    if (!head)
        return 0;

    if (head->compare(key) == 0) {
        Node* temp = head; // save
        head = head->get_next(); // adjust
        delete temp; // delete
        return 1;
    }

    return this->remove(head->get_next(), key);
}

// wrapper to deal with base cases for searching for a node in the list
Activity* LLL::retrieve(const char* key) {
    if (!this->head)
        return NULL;

    return this->retrieve(this->head, key);
}

// recursively traverse the list and display the node that matches the key
Activity* LLL::retrieve(Node*& head, const char* key) {
    if (!head)
        return NULL;

    if (head->compare(key) == 0) { // found it
        return head->get_activity();
    }

    return this->retrieve(head->get_next(), key);
}

// recursively append the given list onto this object
void LLL::append_list(Node* from) {
    if (!from) // nothing else to add
        return;

    this->add(*from->get_activity()); // add it

    this->append_list(from->get_next());
}

// recursively check if lists are equal
bool LLL::is_equal(Node* head, Node* comp) const {
    if (head && !comp) // one finished but other isnt
        return false;

    if (comp && !head)
        return false;

    if (!head || !comp) // both lists finished
        return true;

    if (head->compare(*comp->get_activity()) != 0) // not matching
        return false;

    return this->is_equal(head->get_next(), comp->get_next());
}

// recursively check if head has more nodes than comp
bool LLL::has_more(Node* head, Node* comp) const {
    if (head && !comp)
        return true;

    if (comp && !head)
        return false;

    if (!comp && !head)
        return false;

    return this->has_more(head->get_next(), comp->get_next());
}
