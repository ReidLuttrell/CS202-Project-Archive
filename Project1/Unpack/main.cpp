// Reid Luttrell
// File Purpose : Utilize the classes and functionality to implement the discord application

#include <iostream>
#include <cstring>

#include "node.h"
#include "room.h"
#include "manager.h"
#include "member.h"

int main() {
    Member member("Reid", true);
    Member member2("Karla", true);

    Manager manager;

    std::cout << "Welcome to the chat room!\nThe commands are as follows:\n/quit - safely quit\n/status - check status\n/actions - check action history\n/add - add a new room\n/room - change to room\n/delmessage - delete a message\n/delroom - delete a room\n/search - search for a message\n/reply - reply to a message\n/pin - pin a message\n\n";

    char content[256];
    std::cout << "chat: ";

    std::cin.get(content, 256, '\n');
    std::cin.ignore(10000, '\n');

    while (std::strcmp(content, "/quit") != 0) {

	if (std::strcmp(content, "/status") == 0) {
            member.check_status();

	} else if (std::strcmp(content, "/actions") == 0) {
            member.display_actions();

	} else if (std::strcmp(content, "/add") == 0) {
	    int option;
	    char new_name[256];
	    std::cout << "what type of room? (live=1, private=2, message=3)? ";
	    std::cin >> option;
            std::cin.ignore(10000, '\n'); // maybe don't need

	    std::cout << "what is the name of the room? ";
	    std::cin.get(new_name, 256, '\n');
	    std::cin.ignore(10000, '\n');

	    if (option == 1) {
		LiveChat live = LiveChat(new_name);
		if(!member.add_room(manager, live))
		    std::cout << "unable to add room!\n";

	    } else if (option == 2) {
                PrivateRoom priv = PrivateRoom(new_name, &member, &member2);
		if (!member.add_room(manager, priv))
	            std::cout << "unable to add room!\n";

	    } else if (option == 3) { 	
                MessageBoard board = MessageBoard(new_name);
		if(!member.add_room(manager, board))
	            std::cout << "unable to add room!\n";

	    } else {
		std::cout << "option not recognized!\n";
	    }

	} else if (std::strcmp(content, "/delroom") == 0) {
	    char room_del_name[256];
	    std::cout << "what room to delete? ";
	    std::cin.get(room_del_name, 256, '\n');
	    std::cin.ignore(10000, '\n');

            if(!member.remove_room(manager, room_del_name))
		std::cout << "Unable to remove room!\n";

	} else if (std::strcmp(content, "/delmessage") == 0) {
            char msg_del_name[256];
	    std::cout << "what message to delete? ";
	    std::cin.get(msg_del_name, 256, '\n');
	    std::cin.ignore(10000, '\n');

	    if(!member.remove_message(manager, manager.get_room(), msg_del_name))
		std::cout << "unable to remove message!\n";

	} else if (std::strcmp(content, "/room") == 0) {
	    char new_room[256];
	    std::cout << "what is the name of the room to switch to? ";
	    std::cin.get(new_room, 256, '\n');
	    std::cin.ignore(10000, '\n');

            if (!member.change_room(manager, new_room))
	        std::cout << "Unable to find room!\n";

	} else if (std::strcmp(content, "/search") == 0) {
	    char search_key[256];
	    std::cout << "what would you like to search for? ";
	    std::cin.get(search_key, 256, '\n');
	    std::cin.ignore(10000, '\n');

            if (!member.search(manager, manager.get_room(), search_key)) {
                std::cout << "Unable to find message!\n";
	    }

	} else if (std::strcmp(content, "/reply") == 0) {
            char reply_key[256];
	    std::cout << "what message would you like to reply to? ";
	    std::cin.get(reply_key, 256, '\n');
	    std::cin.ignore(10000, '\n');

	    char reply[256];
	    std::cout << "what is your reply? ";
	    std::cin.get(reply, 256, '\n');
	    std::cin.ignore(10000, '\n');

	    Message message = Message(reply, false);

	    if (!member.reply(manager, manager.get_room(), message, reply_key)) {
                std::cout << "Unable to find message to reply to!\n";
	    }

	} else if (std::strcmp(content, "/pin") == 0) {
            char pin_key[256];
	    std::cout << "what message would you like to pin? ";
	    std::cin.get(pin_key, 256, '\n');
	    std::cin.ignore(10000, '\n');

	    if (!member.pin(manager, manager.get_room(), pin_key)) {
                std::cout << "Unable to find message to pin!\n";
	    }

	} else {

	    Message msg = Message(content, false);

            member.post(manager, manager.get_room(), msg);
            std::cout << "--------------------------------\n";
	}

        std::cout << "chat: ";

        std::cin.get(content, 256, '\n');
        std::cin.ignore(10000, '\n');
    }

    return 0;
}
