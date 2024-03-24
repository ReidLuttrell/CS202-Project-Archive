// Reid Luttrell
// File Purpose - encapulate the data surrouding a member of the chatroom

class Manager;
class Message;
class CLL;
class Room;

// MemberStatus holds the information of a member and provides display functionanlity for this info
class MemberStatus {
protected:
    // name of member
    char* name;
    // whether or not they're online
    bool online;
public: 
    // default constructor null initializes data
    MemberStatus(); 
    // delete the dynamic data
    ~MemberStatus();
    // construct with a given name and online status
    MemberStatus(const char* name, bool online);

    // compare the name with the key
    // return strcmp result
    int compare(const char* key) const;
};

// Member derives from it's status and provides wrapper functionality for the manager's functions
// it also hold's it's action history, and a few unique functionalities
class Member : public MemberStatus {
protected:
    // list of actions taken place by this member
    CLL* actions;
public:
    // default constructor null initializes object
    Member();
    // delete dynamic memory
    ~Member();
    // construct with given name and online status
    Member(const char* name, bool online);
    // copy construct a member with the given member
    Member(const Member& member);

    // display the memberstatus info
    void check_status() const;
    // display the action history
    void display_actions() const;

    // since these functions are wrappers for the manager, we need to pass the manager object
    // we don't have the manager objecct in the class, because we want all members to be using
    // the exact same manager object so that they have the same rooms

    // add a new room to the room list given the key
    // return success
    int add_room(Manager& manager, const Room& room);
    // remove a room from the room list given the key
    // return success
    int remove_room(Manager& manager, const char* key);
    // change to a new room given the key name fo the room
    // returns success
    int change_room(Manager& manager, const char* key);
    // remove a message from a room's message list given the room name and the message key
    // return success
    int remove_message(Manager& manager, const char* room_name, const char* key); 

    // post a message to a room's message list given the room name and the message
    // return success 
    int post(Manager& manager, const char* room_name, const Message& msg);
    // reply to a messaga in a room's message list given the room name, the message key, and the reply message
    // return succsess
    int reply(Manager& manager, const char* room_name, const Message& msg, const char* key);

    // search for a message in a room's message list, given the room name, and message key
    // return success
    int search(Manager& manager, const char* room_name, const char* key);

    // pin a message in a room's message list given the room name and the message key
    int pin(Manager& manager, const char* room_name, const char* key);
};
