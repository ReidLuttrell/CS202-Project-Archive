// Reid Luttrell
// File Purpose : implement the functionality of the action history list
// and all objects and functionality related

#include <cstring>
#include <iostream>
#include "actions.h"

// null initialize action object data
Action::Action() : action(NULL) {};

// delete dynamic action object data
Action::~Action() {
    delete[] this->action;
}

// deep copy given action data into object
Action::Action(const char* action) {
    int actLen = std::strlen(action);
    this->action = new char[actLen + 1];
    std::strcpy(this->action, action);
    this->action[actLen] = '\0';
}

// deep copy given action object's data into this action object
Action::Action(const Action& from) {
    int actLen = std::strlen(from.action);
    this->action = new char[actLen + 1];
    std::strcpy(this->action, action);
    this->action[actLen] = '\0';
}

// display action object data
void Action::display() const {
    std::cout << this->action << '\n';
}

// compare action object data to given key
int Action::compare(const char* key) const {
    return std::strcmp(this->action, key);
}

// null intiailize node data
node::node() : Action(NULL), next(NULL) {};

// deep copy action info into underlying action object and null initialize node object
node::node(const char* action) : Action(action), next(NULL) {};

// deep copy data from action info object into underlying actino object and null intitialize node object
node::node(const Action& from) : Action(from), next(NULL) {};

// deep copy data from node object into underlying action action, and null intitialize node
node::node(const node& from) : Action(from), next(NULL) {};

// return node's next pointer
node*& node::get_next() {
    return this->next;
}

// set node's next pointer
void node::set_next(node* next) {
    this->next = next;
}

// null inititalize circularlist object data
CircularList::CircularList() : rear(NULL) {}

// acts as wrapper to delete all nodes from CircularList
CircularList::~CircularList() {
    if (!this->rear) // list empty
	return;

    this->delete_all(this->rear);
}

/*CircularList::CircularList(const CircularList& from) {

}*/

// wrapper to display all nodes from circular list
// deals with base cases
void CircularList::display_all() const {
    if (!this->rear) // list empty
	return;

    node* front = rear->get_next(); // display front node first
    front->display();

    this->display_all(front->get_next());
}

// recursively display all nodes in CircularList
void CircularList::display_all(node*& rear) const {
    if (rear == this->rear->get_next()) // stop when reached front again
	return;

    rear->display();
    this->display_all(rear->get_next());
}

// recursively delete all nodes in CircularList
void CircularList::delete_all(node*& rear) {
    if (this->rear->get_next() == this->rear) { // one node left
	rear->set_next(NULL);
	delete rear;
	return;
    }

    node* temp = rear->get_next()->get_next(); // save
    delete rear->get_next(); // delete
    rear->set_next(temp); // adjust

    this->delete_all(rear);
}

// default constructor does nothing because this object has no unique data
CLL::CLL() {}

// function add a new node to the CircularList
void CLL::add(const char* to_add) { // may not be recursive
    if (!this->rear) { // empty list
        this->rear = new node(to_add);
	this->rear->set_next(this->rear);
	return;
    }

    node* new_node = new node(to_add); // allocate and construct
    node* temp = this->rear->get_next(); // save
    this->rear->set_next(new_node); // adjust
    new_node->set_next(temp); // adjust
}
