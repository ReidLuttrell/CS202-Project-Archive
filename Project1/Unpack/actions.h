// Reid Luttrell
// File Purpose : Implement the classes that deal with the action history list

// class action holds the action information and provides the display and compare functionality
class Action {
protected:
    // the name of the action
    char* action;
public:
    // default constructor null initializes object info
    Action();
    // delete dynamic information
    ~Action();
    // construct with given action name
    Action(const char* action);
    // copy construct with existing action object
    Action(const Action& from);
   
    // display object info
    void display() const;
    // compare action character array to key character array
    // return strcmp result
    int compare(const char* key) const;
};

// node holds derives from the action object
// and holds a pointer to the next node
// also supplies object oriented functionality
// for modifying this information
class node : public Action {
protected:
    // pointer to next node
    node* next;
public:
    // default constructor null initializes object information
    node();
    // construct node with given action info
    node(const char* action);
    // copy construct node with existing action object
    node(const Action& from);
    // copy construct node with existing node object
    node(const node& from);

    // return the node object's next pointer
    node*& get_next();
    // set the node's next pointer
    void set_next(node* next);
    // return true if the next pointer is valid
    bool if_next() const;
};

// class CircularList enapsulates the linked list
// and manages the displaying and deletion
class CircularList {
public:
    // defualt construct object by null initializing data
    CircularList();
    // deletes dynamic info from object
    ~CircularList();
    //CircularList(const CircularList& from);

    // wrapper to display all the nodes in the list
    void display_all() const;
protected:
    // recursively display all nodes in the list
    void display_all(node*& rear) const;
    // recursively delete all nodes from the list
    void delete_all(node*& rear);
    // the rear node of the list
    node* rear;
};

// class CLL manages the modification of the circular linked list
class CLL : public CircularList {
public:
    // default construct by null initializing data
    CLL();
    //CLL(const CLL& from);

    // add a node to the CircularList given the name of the action
    void add(const char* to_add);
};

