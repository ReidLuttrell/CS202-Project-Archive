// Reid Luttrell
// File Purpose : implements the functionality of the Node object
// and related objects

#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

// null inititalize message data
Message::Message() : msg(NULL), pinned(false) {};

// delete dynamic message data
Message::~Message() {
    delete[] this->msg;
}

// deep copy mesg into object and copy pinned value
Message::Message(const char* msg, bool pinned) {
    int msgLen = std::strlen(msg);
    this->msg = new char[msgLen + 1];
    std::strcpy(this->msg, msg);
    this->msg[msgLen] = '\0';

    this->pinned = pinned;
}

// deep copy given message object's data into this object
Message::Message(const Message& from) {
    int msgLen = std::strlen(from.msg);
    this->msg = new char[msgLen + 1];
    std::strcpy(this->msg, from.msg);
    this->msg[msgLen] = '\0';
    
    this->pinned = from.pinned;
}

// compare msg data to given key
int Message::compare(const char* key) const {
    return std::strcmp(this->msg, key);
}

// display message object's data
void Message::display() const {
    if (this->pinned) // if it's pinned, display that about it
        std::cout << "Pinned:\n";
    std::cout << this->msg << '\n';
}

// return true if the message is pinned
bool Message::is_pinned() const {
    return this->pinned;
}

// null inititalize Node object and underlying message object
Node::Node() : Message(NULL, false), next(NULL) {};

// null intitialize node object data and pass given data into Message object constructor
Node::Node(const char* msg, bool pinned) : Message(msg, pinned), next(NULL) {};

// null inititalize node object dataa and pass existing message object data into this object's message constructor
Node::Node(const Message& from) : Message(from), next(NULL) {};

// null inititalize node and copy message data from existing node into this node's message object
Node::Node(const Node& from) : Message(from), next(NULL) {} // maybe copy over node data too

void Node::write(std::ofstream& file) {
    file << this->msg << '\n';
}

// return the next pointer
Node*& Node::get_next() {
    return this->next;
}

// set the next pointer
void Node::set_next(Node* next) {
    this->next = next;
};
