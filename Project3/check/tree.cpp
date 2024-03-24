// Reid Luttrell
// File Purpose: implement tree functionality

#include "list.h"
#include "tree.h"

#include <iostream>

// null initialize dynamic members
node::node() : left(NULL), right(NULL) {}

// deep copy list over to this node
node::node(const LLL& list) {
    this->copy_list(list);
}

// return left child
node*& node::get_left() {
    return this->left;
}

// return right child
node*& node::get_right() {
    return this->right;
}

// set left child
void node::set_left(node* left) {
    this->left = left;
}

// set right child
void node::set_right(node* right) {
    this->right = right;
}

// null initialize dynamic member
BinarySearchTree::BinarySearchTree() : root(NULL) {}

// deep copy tree to this object
BinarySearchTree::BinarySearchTree(const BinarySearchTree& from) {
    this->copy_tree(this->root, from.root);
}

// wrapper to delete tree
BinarySearchTree::~BinarySearchTree() {
    if (!this->root)
        return;

    this->delete_all(this->root);
}

// recursively walk tree and delete all nodes
void BinarySearchTree::delete_all(node*& root) {
    if (!root)
        return;

    this->delete_all(root->get_left());
    this->delete_all(root->get_right());

    delete root;
    root = NULL;
}

void BinarySearchTree::copy_tree(node*& to, node* from) {

}

// wrapper to display node with activites with given name
void BinarySearchTree::display(const char* name) const {
    if (!this->root)
        return;

    this->display(this->root, name);
}

// recursively walk tree and display node with given name
void BinarySearchTree::display(node* root, const char* name) const {
    if (!root)
        return;

    if (root->compare_head(name) > 0)
        return this->display(root->get_left(), name);
    else if (root->compare_head(name) < 0)
        return this->display(root->get_right(), name);
    else { // match
        std::cout << *root;
    }

}

// wrapper to display all nodes in tree
void BinarySearchTree::display_all() const {
    if (!this->root)
        return;

    this->display_all(this->root);
}

// recursively walk tree and display every node
void BinarySearchTree::display_all(node* root) const {
    if (!root)
        return;

    this->display_all(root->get_left());

    std::cout << *root;

    this->display_all(root->get_right());
}

// wrapper to find by key with subscript operator
Activity* BST::operator[](const char* key) {
    return this->retrieve(key);
}

// wrapper to display all nodes in tree
std::ostream& operator<<(std::ostream& out, const BST& tree) {
    tree.display_all();
    return out;
}

// wrapper to add activity to tree
int BST::add(const Activity& activity) {
    return this->add(this->root, activity);
}

// wrapper to remove activity from tree with given name
int BST::remove(const char* key) {
    if (!this->root)
        return 0;

    return this->remove(this->root, key);
}

// recursively walk to empty node and add activity
int BST::add(node*& root, const Activity& activity) {
    if (!root) {
        root = new node; // make new list
        *root += activity;
        return 1;
    }

    if (root->compare_head(activity) > 0) // check these equalities
        return this->add(root->get_left(), activity);
    else if (root->compare_head(activity) < 0)
        return this->add(root->get_right(), activity);
    else { // match
        *root += activity; // add to list
        return 1;
    }
}

// recursively traverse to IOS, copy data to base, and delete
int BST::remove_inorder_successor(node*& root, node*& base) {
    if (!root)
        return 0;

    if (!root->get_left()) {
        base->copy_list(*root); // copy list over
        root = root->get_right();

        delete root;
        root = NULL;

        return 1;
    }

    return this->remove_inorder_successor(root->get_left(), base);
}

// recursively find activity with key and remove it
int BST::remove(node*& root, const char* key) {
    if (!root)
        return 0;

    if (root->compare_head(key) > 0) {
        return this->remove(root->get_left(), key);
    } else if (root->compare_head(key) < 0) {
        return this->remove(root->get_right(), key);
    } else { // match
        root->remove(key); // remove activity
        
        if (root->is_empty()) { // if its empty now remove node
            if (!root->get_left()) {
                node* temp = root->get_right();
                delete root;
                root = temp;
                return 1;
            } else if (!root->get_right()) {
                node* temp = root->get_left();
                delete root;
                root = temp;
                return 1;
            }

            if (!root->get_right()->get_left()) { // two children but no root->right->left
                root->copy_list(*root->get_right()); // copy list over

                node* temp = root->get_right()->get_right();
                delete root->get_right();
                root->set_right(temp); 
            } else {
                return this->remove_inorder_successor(root->get_right(), root);
            }
        }
    }
    return 1; // something got removed fersure so ret success
}

// wrapper to retrieve activity with given name
Activity* BST::retrieve(const char* key) {
    if (!this->root)
        return NULL;

    return this->retrieve(this->root, key);
}

// recursively walk tree and return pointer to activity with given name
Activity* BST::retrieve(node*& root, const char* key) {
    if (!root)
        return NULL;

    if (root->compare_head(key) > 0) {
        return this->retrieve(root->get_left(), key);
    } else if (root->compare_head(key) < 0) {
        return this->retrieve(root->get_right(), key);
    } else { // match
        return (*root)[key]; // operator overloading magic 
    }
}

void BST::buy(const char* key, LLL& order_list, int& total) {
    Activity* activity = this->retrieve(key);
    activity->add_total(total);

    order_list.add(*activity);
}
