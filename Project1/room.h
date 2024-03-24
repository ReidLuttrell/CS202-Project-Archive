// Reid Luttrell
// file purpose - prototype all classes to provide data and functionality for the chat rooms

#include <fstream>

class Message;
class Node;
class Member;

// Linked list class
// holds a linked list of messages
class LinkedList {
public:
    // default conststructor to null initialize list
    LinkedList();
    // copy constructor to load existing list
    LinkedList(const LinkedList& from);
    // delete entire list
    ~LinkedList();
    // wrapper to write all nodes to a file
    void write_all(std::ofstream& file);
    // display every Message in the list, wrapper function
    void display_all() const;
protected:
    // recursively write all the nodes data to a file
    void write_all(Node*& head, std::ofstream& file);
    // copy one linked list to another, used for copy constructor
    void copy_list(Node*& to, Node* from);
    // recursive method for deleting list
    void delete_all(Node*& head);
    // recursive method for displaying list
    void display_all(Node* head) const;
    // the starting node of the list, the first message.
    Node* head;
};

// LLL class
// ALlows linear linked list functionality by encapsulating
// the Linked List and treating it as such
class LLL : public LinkedList {
public:
    // default constructor null initializes the linked list
    LLL();
    // copy constructor takes an existing LLL and copies over to this object
    LLL(const LLL& from);

    // add a new message to the linked list - wrapper
    // return success flag
    int add(const Message& to_add);
    // remove a message from the linked list based on the key - wrapper
    // return success flag
    int remove(const char* key);
    // retrieve a message from the linked list based on the key - wrapper
    // return success flag
    int search(const char* key);
    // find message, remomve, and add to the end of the list based on the key - wrapper
    void push_to_tail(const char* key);
protected:
    // recursive implementation to add message to list
    // return success flag
    int add(Node*& head, const Message& to_add);
    // recursive implementation to remove message based on key
    // return success flag
    int remove(Node*& head, const char* key);
    // recursive implementation to retrieve message based on key
    // return success flag
    int search(Node*& head, const char* key);
    // recursive implementation to remove message and add to the end of list
    void push_to_tail(Node*& head, const char* key);
};

// the room base class, structurally an LLL,
// holds room information and basic functionality
class Room : public LLL {
protected:
    // the name of the room
    char* name;
public:
    // default constructor null initializes
    Room();
    // deletes dynamic information of the room
    virtual ~Room();
    // constructs a room given a room name
    Room(const char* new_name);
    // constructs a room given a name and a list of messages
    Room(const char* new_name, LLL msgs);
    // copy constructs a room given a proprietary room object
    Room(const Room& from);

    // write the room name to the file
    void write_name(std::ofstream& file);

    // compare the room name with the argument
    // return strcmp output
    int compare(const char* other);

    // add a new message to the message list
    void post(const char* member_name, const Message& msg);

    // find a message given the key, display the message, post a response
    // return success flag
    virtual int reply(const char* member_name, const Message& msg, const char* key);
    // find a message given the key, push it to the tail of the list, and mark it pinned
    // return success flag
    virtual int pin(const char* key);
};

// a specialization of the room base class with two members allowed and different display functionality
class PrivateRoom : public Room {
protected:
    // the first memeber allowed
    Member* mem_one;
    /// the second member allowed
    Member* mem_two;
public:
    // construct a private room with a name and two members
    PrivateRoom(const char* new_name, Member* one, Member* two);
    // construct a private room with a name, two members, and a list of messages
    PrivateRoom(const char* new_name, Member* one, Member* two, LLL msgs);
    // copy constructor for add_room 
    PrivateRoom(const PrivateRoom& other);
    // delete member pointers 
    ~PrivateRoom(); 
    // check if the name passed in is allowed in the room
    bool check_access(const char* name);
};

// a chat with messages coming in real time, default display functionality
class LiveChat : public Room {
public:
    // default construct a live chat
    LiveChat();
    // construct a live chat with a name
    LiveChat(const char* new_name);
    // construct a live chat with a name and list of messages
    LiveChat(const char* new_name, LLL msgs);

    // override to deny access in this room type
    int pin(const char* key);
};

// a specialization of the base where messages cannot be replied to and the display functionality is unique
class MessageBoard : public Room {
public:
    // default construct a message board
    MessageBoard();
    // construct a message board with a name
    MessageBoard(const char* new_name);
    /// construct a message board with a name and a list of messages
    MessageBoard(const char* new_name, LLL msgs);
    // overload to deny access in this room type
    int reply(const char* member_name, const Message& msg, const char* key);
};
