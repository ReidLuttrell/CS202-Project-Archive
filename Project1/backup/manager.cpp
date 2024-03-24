// Reid Luttrell
// File Purpose - manage the functionality of the rooms in an encapsulated manner
// implement said functionality in this file

#include <iostream>
#include <cstring>
#include <fstream>
#include "manager.h"
#include "room.h"
#include "node.h"

// allocate space given the size
Manager::Manager(int sz) : size(sz) {
    if (size <= 0) { // array not big enough to habitate any rooms
        return;
    }

    const char* def_name = "default"; // add a default room
    int lenName = std::strlen(def_name);
    this->current_room = new char[lenName + 1];
    std::strcpy(this->current_room, def_name);
    this->current_room[lenName] = '\0';

    this->rooms = new Room*[this->size]; // allocate space for array of pointers with the size

    for (int i = 0; i < this->size; ++i) {
        this->rooms[i] = NULL; // null initialize
    }

    this->load_from_file();
};

// delete all room pointers from the array and the array itself
Manager::~Manager() {

    this->save_to_file();
    
    if (!this->rooms) // nothing to elete
	return;

    delete[] this->current_room; // delete current room name

    int i = 0;
    this->delete_all(this->rooms, i);

    delete[] this->rooms; // delete array itself
};

// recursive method to delete all rooms
void Manager::delete_all(Room** rooms, int& idx) { // to demonstrate i know how to do this type of recursion if need be
    if (idx >= this->size)
        return;

    if (rooms[idx])
	delete rooms[idx];

    this->delete_all(rooms, ++idx);
}

// pull array and linked list data from the file
// and load it into manager object
void Manager::load_from_file() {
    std::ifstream file("data.txt");
    if (!file.is_open())
	return;

    char room_name[256];

    while (file.getline(room_name, 256)) {
        char message[256];
	file.get(message, 256, '\n');
	file.ignore(10000, '\n');

        LLL list;

        while (message[0] != '*') { // while it's not an asterisk or end of file
             Message msg(message, false);
	     list.add(msg);

	     file.get(message, 256, '\n');
	     file.ignore(10000, '\n');
	}

        if (!file.eof()) {
            for (int i = 0; i < this->size; ++i) {
                if (!this->rooms[i]) {
	            this->rooms[i] = new Room(room_name, list);
                    break;
		}
	    }
	}
    }

    file.close();
}

// pull array and linked list data from object
// and load it into the data file
void Manager::save_to_file() {
    std::ofstream file("data.txt");

    for (int i = 0; i < this->size; ++i) {
        if(this->rooms[i]) {
            this->rooms[i]->write_name(file);
            this->rooms[i]->write_all(file);
	    file << "*\n"; // end of room marker
	}
    }

    file.close();
}

// find index in array that holds room with given key
int Manager::find_room_index(const char* key, int& index) const {
    for (int i = 0; i < this->size; ++i) { // it wouldn't make sense to make this recursive, because it would make uneccesary stack frames
	                                   // to force recursion onto a purely iterative problem.
	if (this->rooms[i]) { // does room exist in index?
            if (this->rooms[i]->compare(key) == 0) { // is it the one we want?
                index = i; // load index
	        return 1;
	    }
	}
    }
    return 0;
}

// change current room name to key
int Manager::change_room(const char* member_name, const char* key) {
    int i;
    if (this->find_room_index(key, i)) {
	PrivateRoom* priv = dynamic_cast<PrivateRoom*>(this->rooms[i]);

        if (priv) {
            std::cout << "Requesting to join private room...\n";
            if (!priv->check_access(member_name)) {
                std::cout << "Access denied!\n";
	        return 0; 
	    }
	    std::cout << "Access granted!\n";
	}

	delete[] this->current_room; // delete previous name memory

	int lenName = std::strlen(key);
        this->current_room = new char[lenName + 1];
        std::strcpy(this->current_room, key); // deep copy new name
	this->current_room[lenName] = '\0';

        this->display_room(key); // display new room
	return 1;
    }
    return 0;
}

// return current room name
char* Manager::get_room() {
    return this->current_room;
}

// add a new room to the array
int Manager::add_room(const Room& room) {

    const PrivateRoom* priv = dynamic_cast<const PrivateRoom*>(&room); // check what kind it is with downcasting
    const MessageBoard* mess = dynamic_cast<const MessageBoard*>(&room);
    const LiveChat* live = dynamic_cast<const LiveChat*>(&room);

    for (int i = 0; i < this->size; ++i) {
        if (!rooms[i]) { // empty space in array
            if (priv) // construct based on validity
		rooms[i] = new PrivateRoom(*priv);
	    else if (mess)
		rooms[i] = new MessageBoard(*mess);
	    else if (live)
                rooms[i] = new LiveChat(*live);
	    else
		return 0;
	    return 1;
	}
    }
    return 0;
};

// remove room with given name from array
int Manager::remove_room(const char* name) {
    int i;
    if (this->find_room_index(name, i)) { // find room with that name
        delete this->rooms[i]; // delete it
        this->rooms[i] = NULL;
	return 1;
    }
    return 0;
}

// wrapper remove a message with given key from the room with given name
int Manager::remove_message(const char* room_name, const char* key) {
    int i;
    if (this->find_room_index(room_name, i)) { // find room
        this->rooms[i]->remove(key); // remove message
	return 1;
    }

    return 0;
}

// wrapper to add new message to room's message linked list
int Manager::post(const char* member_name, const char* room_name, const Message& msg) {
    int i; 
    if (this->find_room_index(room_name, i)) { // find room with given name
        this->rooms[i]->post(member_name, msg); // post to room, associate with member
        return 1;
    }
    
    return 0;
}

// wrapper to search for message in room's message list
int Manager::search(const char* member_name, const char* room_name, const char* key) {
   int i;
   if (this->find_room_index(room_name, i)) { // find room
       return this->rooms[i]->search(key); // search for it within the object
   }

   return 0;
}

// wrapper to pin a message in a room's message list
int Manager::pin(const char* member, const char* room_name, const char* key) {
    int i;
    if (this->find_room_index(room_name, i)) { // find room
        this->rooms[i]->pin(key); // pin message
	return 1;
    }
    return 0;
}

// wrapper to reply to a message in the given room, with the given message
int Manager::reply(const char* member_name, const char* room_name, const Message& msg, const char* key) {
    int i;
    if (this->find_room_index(room_name, i)) { // find room
        return this->rooms[i]->reply(member_name, msg, key); // reply to message
    }
    
    return 0;
}

// wrapper to display a room's messages
int Manager::display_room(const char* name) const {
    int i;
    if (this->find_room_index(name, i)) { // find room
        this->rooms[i]->display_all(); // display messages
        return 1;
    }

    return 0;
}
