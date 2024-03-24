// Reid Luttrell
// File Purpose : prototype tree functionality

class LLL;

// class node is a subset of LinkedList
// node for the BST
class node : public LLL {
public:
    // default constructor null initializes
    node();
    // create a node with given linkedlist stored
    node(const LLL& list);

    // returns left pointer
    node*& get_left();
    // returns right pointer
    node*& get_right();
    // sets left pointer
    void set_left(node* left);
    // sets right pointer
    void set_right(node* right);
protected:
    // pointer to left child
    node* left;
    // pointer to right child
    node* right;
};

// BinarySearchTree holds the root of the list
// and treats it as a binary search tree
class BinarySearchTree {
public:
    // default constructor null initializes
    BinarySearchTree();
    // construct a binary search tree given one
    BinarySearchTree(const BinarySearchTree& from);
    // destructor deletes treee
    ~BinarySearchTree();

    // display tree node with activities of the given name - wrapper
    void display(const char* name) const;
    // display all activites in the tree - wrapper
    void display_all() const;
protected:
    // recursively delete all nodes of tree
    void delete_all(node*& root);
    // recursively copy all nodes of tree
    void copy_tree(node*& to, node* from);

    // recursively traverse tree and display list with activities of given name
    void display(node* root, const char* name) const;
    // recursively traverse tree and display all nodes
    void display_all(node* root) const;

    // the root node of the binary search tree
    node* root;
};

// BST is an ADT that encapsulates BinarySearchTree
class BST : public BinarySearchTree {
public:
    // find the Activity with the given key
    // return reference to activity
    Activity* operator[](const char* key);

    // display the tree
    // return stream
    friend std::ostream& operator<<(std::ostream& out, const BST& tree);

    // add a new activity to the tree - wrapper
    // return success
    int add(const Activity& activity);
    // remove activity from the tree with key - wrapper
    // return success
    int remove(const char* key);
    // retrieve activity from the tree with key - wrapper
    // return pointer to Activity
    Activity* retrieve(const char* key);
    // purchase an activity, update total price, and add it onto your order list
    void buy(const char* key, LLL& order_list, int& total);
protected:
    // recursively remove the inorder successor and copy data over
    // return success
    int remove_inorder_successor(node*& root, node*& base);
    // recursively add activity to tree
    // return success
    int add(node*& root, const Activity& activity);
    // recursively remove activity from tree with key
    // return success
    int remove(node*& root, const char* key);
    // recursively retrieve activity from the list
    // return pointer to activity
    Activity* retrieve(node*& root, const char* key);
};
