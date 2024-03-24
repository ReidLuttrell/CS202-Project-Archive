// Reid Luttrell
// Manager.h - responsible for the memory and functionality of the room array

#include <fstream>

class Room;
class Message;
class LLL;

// holds the array of rooms, the size of the array, and the name of the current room
class Manager {
protected:
    // array of pointers to room objects, pointers to check for validity
    Room** rooms;
    const int size; // 10 rooms allowed by default
    char* current_room; // the name of the current room being posted to and displayed
public:
    // default construct the room with a capacity of 10 rooms by default
    Manager(int sz = 10);
    // recursive method to null initialize rooms
    void null_initialize(int& idx);
    // delete all rooms from array acts as wrapper for delete_all
    ~Manager();

    // recursively delete all the rooms
    void delete_all(Room** rooms, int& idx);

    // load conversation data from the data file
    void load_from_file();
    // recursively pull from file the data needed to populate room array
    void load_from_file(std::ifstream& file, char* room_name);
    // recursively load messages from file into an LLL
    void load_messages(std::ifstream& file, LLL& list);
    /// recursively load messages in list into a new room object in the array
    void load_room(const char* room_name, LLL& list, int& idx);
    // save conversation data to the data file
    void save_to_file();

    // recursive method to write room data to file
    void write_all(int& idx, std::ofstream& file);

    // wrapper to find the index of the room with the given key
    // return success
    int find_room_index(const char* key, int& index) const;
    // recursively search for the room index with the matching key
    int find_room_index(const char* key, int& index, int& idx) const;
    // change the room to the given key name
    // return success flag
    int change_room(const char* member_name, const char* key);

    // get the current room name from the objectl
    // return name
    char* get_room();

    // add a new room to the array given in the parameter
    int add_room(const Room& room);
    // recursively add a new room to the room array
    int add_room(const Room& room, int& idx);
    // remove the room with the given name
    // return success flag
    int remove_room(const char* name);

    // remove a message with the given key from the room with the given room name
    // return success flag
    int remove_message(const char* room_name, const char* key);

    // add a new message to the room with the given name, and associate it with the member who posted it
    // return success
    int post(const char* member_name, const char* room_name, const Message& msg);
   
    // search for the message with the given key in the room with the given room name
    // return success
    int search(const char* member_name, const char* room_name, const char* key);
    // pin the message with the given key in the room with the given room name
    // return success
    int pin(const char* member_name, const char* room_name, const char* key);
    // reply to the message with the given key in the room with the given room name, associate with member name
    // return success
    int reply(const char* member_name, const char* room_name, const Message& msg, const char* key);
    // display the message in the room with the given room name
    // return success
    int display_room(const char* name) const;
};
