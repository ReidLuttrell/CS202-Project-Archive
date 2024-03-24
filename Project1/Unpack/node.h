// Reid Luttrell
// File Purpose : Hold's the information and functionality of the Node object
// which is a Message in its underlying form

#include <fstream>

// class message holds the information of the message along with
// providing compare and display functionality
class Message {
protected:
    // the message data itself
    char* msg;
    // whether or not the message is pinned
    bool pinned; // can be used as a flag to insert before the linked list, pinning a message will
                 // involve pushing to the end of the linked list, keeping it pinned will mean
		 // checking if a message is pinned before inserting after it, if it is,
		 // push before it, it its not, keep going until end of list or until pinned message found
		 // if the message to push is a pinned one, just go until the end of list to insert
public:
    // default constructor null initializes object
    Message();
    // deletes dynamic information from object
    ~Message();
    // construct object with given msg and pinned values
    Message(const char* msg, bool pinned);
    // copy construct message with existing message object
    Message(const Message& from);
    // compare the msg data with the given key
    // return strcmp result
    int compare(const char* key) const;
    // display the message object info
    void display() const;
    // return whether or not the message is pinned
    bool is_pinned() const;
};

// class Node derives from Message and also holds data
// for the next Node in the list, as well as supply
// functionality to retrieve, set, and check information
// about the Node
class Node : public Message {
protected:
    // the next Node in the list
    Node* next;
public:
    /// default constructor null inititalizes object data
    Node();
    // constructs a Node with the given message and pinned data
    Node(const char* message, bool pinned);
    // constructs a node given an existing message object's data
    Node(const Message& message);
    // copy constructs a node given an existing node
    Node(const Node& from);

    // write node's message data to the file
    void write(std::ofstream& file);

    // returns the next pointer
    Node*& get_next();
    // sets the next pointer
    void set_next(Node* next);
    // returns true if the next pointer is valid
    bool if_next() const;
};
