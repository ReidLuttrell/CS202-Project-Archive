// Reid Luttrell
// File Purpose : Implement the functionality of all objects member related

#include <cstring>
#include <iostream>
#include "member.h"
#include "room.h"
#include "manager.h"
#include "actions.h"

// null initialize status data
MemberStatus::MemberStatus() : name(NULL), online(false) {}

// delete dynamic status data
MemberStatus::~MemberStatus() {
    delete[] this->name;
    this->online = false;
}

// construct a status object with the given data, deep copy
MemberStatus::MemberStatus(const char* name, bool online) {
    int lenName = std::strlen(name);
    this->name = new char[lenName + 1];
    std::strcpy(this->name, name);
    this->name[lenName] = '\0';

    this->online = online;
}

// strcmp the stored name and the given key and return the result
int MemberStatus::compare(const char* key) const {
    return std::strcmp(this->name, key);
}

Member::Member() {
    this->actions = new CLL; // default construct with a new CLL of actions
}

Member::~Member() {
    delete this->actions; // delete the CLL pointer
}

// load given status info into the parent object
Member::Member(const char* name, bool online) : MemberStatus(name, online) {
    this->actions = new CLL; // allocate new actions CLL
}

Member::Member(const Member& member) : MemberStatus(member.name, member.online) {
    this->actions = new CLL;
}

// display the member's status info
void Member::check_status() const {
    this->actions->add("checked status");
    std::cout << "Name: " << this->name << '\n';
    std::cout << "Online: " << this->online << '\n';
}

// display the CLL of actions
void Member::display_actions() const {
    std::cout << "displaying actions:\n";
    this->actions->display_all();
}

// wrapper to add new room given manager and room
int Member::add_room(Manager& manager, const Room& room) {
    this->actions->add("added room");
    return manager.add_room(room);
}

// wrapper to remove room given manager and key of room
int Member::remove_room(Manager& manager, const char* key) {
    this->actions->add("removed room");
    return manager.remove_room(key);
}

// wrapper to change room given manager and key of room
int Member::change_room(Manager& manager, const char* key) {
    this->actions->add("changed room");
    return manager.change_room(this->name, key);
}

// wrapper to remove message given manager, room name, and key of message
int Member::remove_message(Manager& manager, const char* room_name, const char* key) {
    this->actions->add("removed message");
    return manager.remove_message(room_name, key);
}

// wrapper to post a message given manager, room name, and message to add
int Member::post(Manager& manager, const char* room_name, const Message& msg) {
    this->actions->add("posted message");
    return manager.post(this->name, room_name, msg);
}

// wrapper to reply to message given manager, room name, key of message to reply to, and message to reply with
int Member::reply(Manager& manager, const char* room_name, const Message& msg, const char* key) {
    this->actions->add("replied to message");
    return manager.reply(this->name, room_name, msg, key);
}

// wrapper to search for message given manager, room name, and key of message
int Member::search(Manager& manager, const char* room_name, const char* key) {
    this->actions->add("searched for message");
    return manager.search(this->name, room_name, key);
}

// wrapper to pin message given manager, room name, and key of message
int Member::pin(Manager& manager, const char* room_name, const char* key) {
    this->actions->add("pinned message");
    return manager.pin(this->name, room_name, key);
}

