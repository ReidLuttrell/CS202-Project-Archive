// Reid Luttrell
// File Purpose : Implement the functionality of all classes room related

#include <iostream>
#include <cstring>
#include <fstream>
#include "room.h"
#include "node.h"
#include "member.h"

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
 
    this->display_all(this->head);
}

// recursively traverse list and display each node
void LinkedList::display_all(Node* head) const {
    if(!head)
        return;

    head->display(); // display the message

    this->display_all(head->get_next());
}

// write all the nodes data to a file
void LinkedList::write_all(std::ofstream& file) {
    if(!this->head)
        return;

    this->write_all(this->head, file);
}

void LinkedList::write_all(Node*& head, std::ofstream& file) {
    if(!head)
	return;

    head->write(file);

    this->write_all(head->get_next(), file);
}

// default does nothing because this object itself has no data
LLL::LLL() {}

// copy constructo just calls LinkedList's copy constructor because it has the data
LLL::LLL(const LLL& from) : LinkedList(from) {};

// wrapper to add a new node to the underlinked linkedlist
int LLL::add(const Message& to_add) {
    return this->add(this->head, to_add);
}

// recursively traverse to the end of the list and add the new node
int LLL::add(Node*& head, const Message& to_add) {
    if (!head) {
        head = new Node(to_add); // allocate memory and construct
	return 1;
    }

    if (head->is_pinned()) {
        Node* temp = head;
        head = new Node(to_add);
        head->set_next(temp);
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

    if (head->compare(key) == 0) { // does key match?
	Node* temp = head; // save
	head = head->get_next(); // adjust
	delete temp; // delete
	return 1;
    }

    return this->remove(head->get_next(), key);
}

// wrapper to deal with base cases for searching for a node in the list
int LLL::search(const char* key) {
    if (!this->head)
	return 0;

    return this->search(this->head, key);
}

// recursively traverse the list and display the node that matches the key
int LLL::search(Node*& head, const char* key) {
    if (!head)
        return 0;

    if (head->compare(key) == 0) { // does key match?
        std::cout << "found message: \n";
	head->display();
	return 1;
    }

    return this->search(head->get_next(), key);
}

// wrapper for dealing iwth base cases for removing matching node and pushing it to the end
void LLL::push_to_tail(const char* key) {
    if (!this->head->get_next()) { // one node
        delete this->head; //delete it
	this->head = new Node(key, true); // reallocate it marked as pinned
	return;
    }

    if (!this->head)
        return;

    this->remove(key); // remove the node witht he key
    this->push_to_tail(this->head, key);
}

void LLL::push_to_tail(Node*& head, const char* key) {
    if (!head) {
        head = new Node(key, true); // end is found and node is entered as pinned
	return;
    }

    this->push_to_tail(head->get_next(), key);
}

// default initialize name
Room::Room() : name(NULL) {};

// delete name
Room::~Room() {
    delete[] this->name;
}

// allocate new memory for the name and give it new_name's value
Room::Room(const char* new_name) {
    int lenName = std::strlen(new_name);
    this->name = new char[lenName + 1];
    std::strcpy(this->name, new_name);
    this->name[lenName] = '\0';
}

// deep copy new_name into the object and also construct with the given LLL
Room::Room(const char* new_name, LLL msgs) : LLL(msgs) {
    int lenName = std::strlen(new_name);
    this->name = new char[lenName + 1];
    std::strcpy(this->name, new_name);
    this->name[lenName] = '\0';
}

// copy the name from an existing rooom object
Room::Room(const Room& from) : LLL(from) {
    int lenName = std::strlen(from.name);
    this->name = new char[lenName + 1];
    std::strcpy(this->name, from.name);
    this->name[lenName] = '\0';
}

// write the room's name to the file
void Room::write_name(std::ofstream& file) {
    file << this->name << '\n';
}

// compare the objects name with the given name
int Room::compare(const char* other) {
    return std::strcmp(this->name, other);
}

// post a message to the list witht he members name attached
void Room::post(const char* member_name, const Message& msg) {
    this->add(msg); // add it to the list
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << member_name << ": \n"; // shove chat off the screen and display name
    this->display_all(); // display the whole chat again, this makes it seem like it was simply added
}

// search for the key in the list, add the message to the list, display the member name and the message
int Room::reply(const char* member_name, const Message& msg, const char* key) {
    if (this->search(key)) {
        this->add(msg);
	std::cout << member_name << ": \n";
        msg.display();
	return 1;
    }

    return 0;
}

// pin the comment by pushing it to the tail
int Room::pin(const char* key) {
    if (this->search(key)) {
        this->push_to_tail(key);
	return 1;
    }

    return 0;
}

// load the room object with the name, and load the private room object with the mebmers
PrivateRoom::PrivateRoom(const char* name, Member* one, Member* two) : Room(name)/*, mem_one(one), mem_two(two)*/ {
    this->mem_one = new Member(*one); // need destructor now
    this->mem_two = new Member(*two);
}

// load the room object with the name and messages, load the private room object with the members
PrivateRoom::PrivateRoom(const char* name, Member* one, Member* two, LLL msgs) : Room(name, msgs), mem_one(one), mem_two(two) {};

PrivateRoom::PrivateRoom(const PrivateRoom& other) : Room(other) {
    this->mem_one = new Member(*other.mem_one);
    this->mem_two = new Member(*other.mem_two);
};

PrivateRoom::~PrivateRoom() {
    delete this->mem_one;
    delete this->mem_two;
}

// compare the stored memebers names to the given name
// and return true if they match
bool PrivateRoom::check_access(const char* name) {
    if (mem_one->compare(name) == 0) {
        std::cout << "Welcome, " << name << ".\n";
	return true;
    } else if (mem_two->compare(name) == 0) {
        std::cout << "Welcome, " << name << ".\n";
	return true;
    }
    return false;
}

// do nothing, this object has no unique memory
LiveChat::LiveChat() {};

// load the room object with the name
LiveChat::LiveChat(const char* name) : Room(name) {};

// load the room object with the name and messages
LiveChat::LiveChat(const char* name, LLL msgs) : Room(name, msgs) {};

int LiveChat::pin(const char* key) {
    std::cout << "Pin is unavailable for live chats!\n";
    return 1;
}

// do nothing, this object has no unique memory
MessageBoard::MessageBoard() {};

// load the room object with the name
MessageBoard::MessageBoard(const char* name) : Room(name) {};

// load the room object with the name and messages
MessageBoard::MessageBoard(const char* name, LLL msgs) : Room(name, msgs) {};

int MessageBoard::reply(const char* member_name, const Message& msg, const char* key) {
    std::cout << "Reply is unavailable for message boards!\n";
    return 1;
}
