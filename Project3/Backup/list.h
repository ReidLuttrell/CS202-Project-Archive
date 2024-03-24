// Reid Luttrell
// File Purpose : prototype list functionality

#include <fstream>

const int MAX_BYTE = 256;
const int BIG_NUMBER = 10000;

// class activity is the base class for all activities
class Activity {
public:
    // default constructor null initializes
    Activity();
    // construct and load parameters
    Activity(const char* name, const char* desc);
    // delete dynamic info
    virtual ~Activity();
    // copy construct an activity object
    Activity(const Activity& from);
 
    // load an activity object into this object
    Activity& operator=(const Activity& other);

    // check if the names are the same given activity
    bool operator==(const Activity& other) const;
    // check if the names are the same given name
    bool operator==(const char* key) const;
    // check if the names arent the same given activity
    bool operator!=(const Activity& other) const;
    // check if the names arent the same given name
    bool operator!=(const char* key) const;

    // compare name to given key
    int compare(const char* key) const;
    // compare name of two activities
    int compare(const Activity& to) const;

    // add price onto total
    virtual void add_total(int& total) const;

    // display object data
    virtual void display() const;
    // load object data
    virtual void read();
protected:
    // name of activity
    char* name;
    // description of activity
    char* desc;
};

// subset of activity that holds coffee information
class Coffee : public Activity {
public:
    // default constructor null initializes
    Coffee();
    // destructor deletes dynamic info
    virtual ~Coffee();
    // construct object with given coffee object
    Coffee(const Coffee& from);

    // add price onto total
    virtual void add_total(int& total) const;

    // display object info
    virtual void display() const;
    // load object info
    virtual void read();
protected:
    // origin of the coffee
    char* origin;
    // price of the coffee
    int price;
};

// subset of activity that holds game information
class Game : public Activity {
public:
    // default constructor null initializes
    Game();
    // destructor deletes dynamic info
    virtual ~Game();
    // construct Game object with given game object
    Game(const Game& from);

    // display object info
    virtual void display() const;
    // load object info
    virtual void read();
protected:
    // type of game
    char* type;
};

// subset of activity that holds baked good information
class Bakery : public Activity {
public:
    // default constructor null initializes
    Bakery();
    // construct Bakery object with given object
    Bakery(const Bakery& from);

    // add price onto total
    virtual void add_total(int& total) const;

    // display object information
    virtual void display() const;
    // load object information
    virtual void read();
protected:
    // price of item
    int price;
};

// a node in the linked list
class Node {
protected:
    Activity* activity;
    // the next Node in the list
    Node* next;
public:
    /// default constructor null inititalizes object data
    Node();
    ~Node();
    // constructs a node given an existing message object's data
    Node(const Activity& activity);
    // copy constructs a node given an existing node
    Node(const Node& from);

    // compare key to activity name
    int compare(const char* key);
    // compare activity to given activity
    int compare(const Activity& other);

    // return activity pointer
    Activity*& get_activity();
    // returns the next pointer
    Node*& get_next();
    // sets the next pointer
    void set_next(Node* next);
};

// Linked list class
// holds a linked list of activities
class LinkedList {
public:
    // default conststructor to null initialize list
    LinkedList();
    // copy constructor to load existing list
    LinkedList(const LinkedList& from);
    // delete entire list
    ~LinkedList();

    // compare the names of the head of the list given key
    // return comparison
    int compare_head(const char* key);
    // compare the names of the head of hte list given activity
    // return comparison
    int compare_head(const Activity& activity);

    // copy given linked list into this object
    void copy_list(const LinkedList& from);
    // display every Activity in the list, wrapper function
    void display_all() const;
protected:
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

    // copy given linked list to this one
    // return reference to new list
    LLL& operator=(const LLL& other);
    // append linked list onto this one
    // return copy
    LLL operator+(const LLL& other);
    // add activity to this linked list
    // return copy
    LLL operator+(const Activity& to_add);
    // append list onto this one
    // return reference to new list
    LLL& operator+=(const LLL& other);
    // add activity to this list
    // return reference to new list
    LLL& operator+=(const Activity& to_add);
    // return whether lists are equal
    bool operator==(const LLL& other) const;
    // return whether lists are not equal
    bool operator!=(const LLL& other) const;
    // returns whether or not this list has more nodes than given list
    bool operator>(const LLL& other) const;
    // returns whether or not this list has less nodes than given list
    bool operator<(const LLL& other) const; 
    // returns whether or not this list has more or equal nodes to given list
    bool operator>=(const LLL& other) const;
    // returns whether or not this list has less or equal nodes to given list
    bool operator<=(const LLL& other) const;
    // retrieve based on key
    Activity* operator[](const char* key);
   
    // display the linked list
    // return stream
    friend std::ostream& operator<<(std::ostream& stream, const LLL& list);

    // returns whether or not the list is empty
    bool is_empty() const;

    // add a new message to the linked list - wrapper
    // return success flag
    int add(const Activity& to_add);
    // remove an activity from the linked list based on the key - wrapper
    // return success flag
    int remove(const char* key);
    // retrieve an activity from the linked list based on the key - wrapper
    // return success flag
    Activity* retrieve(const char* key);
protected:
    // recursive implementation to add activity to list
    // return success flag
    int add(Node*& head, const Activity& to_add);
    // recursive implementation to remove activity based on key
    // return success flag
    int remove(Node*& head, const char* key);
    // recursive implementation to retrieve activity based on key
    // return success flag
    Activity* retrieve(Node*& head, const char* key); 
    // add list onto the end of this one
    void append_list(Node* from);
    // return whether or not the lists match
    bool is_equal(Node* head, Node* comp) const;
    // return whether or not head has more nodes than comp
    bool has_more(Node* head, Node* comp) const;
};

