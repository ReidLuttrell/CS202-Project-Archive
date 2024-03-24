// Reid Luttrell
// File Purpose: Implement client program functionality

#include <iostream>
#include <cstring>

#include "list.h"
#include "tree.h"

int main() {
    BST tree;
    LLL in_house;
    LLL out_house;

    char command[MAX_BYTE];

    int total = 0;

    std::cout << "Welcome to the coffee shop!\n";
    std::cout << "Commands: \n\tadd: add a new activity\n\tremove: remove an existing activity\n\tsearch: find an existing activity\n\tdisplay_all: display all activities\n\tbuy: purchase an item\n\tquit: exit program\n\n";

    std::cout << "command: ";
    std::cin.get(command, MAX_BYTE, '\n');
    std::cin.ignore(BIG_NUMBER, '\n');
    
    while (std::strcmp(command, "quit") != 0) {
        if (std::strcmp(command, "add") == 0) {
            int option;
            std::cout << "What type of activity to add? (1) Coffee, (2) Game, (3) Baked Good: ";
            std::cin >> option;
            std::cin.ignore(BIG_NUMBER, '\n');

            Activity* activity;
            if (option == 1) {
                activity = new Coffee;
            } else if (option == 2) {
                activity = new Game;
            } else if (option == 3) {
                activity = new Bakery;
            } else {
                std::cout << "\nOption not recognized!\n\n";
                continue;
            }

            activity->read();
            tree.add(*activity);
            delete activity;
            
        } else if (std::strcmp(command, "remove") == 0) {
            char remove_key[MAX_BYTE];
            std::cout << "Enter the name of activity to remove: ";
            std::cin.get(remove_key, MAX_BYTE, '\n');
            std::cin.ignore(BIG_NUMBER, '\n');

            if (!tree.remove(remove_key))
                std::cout << "Unable to remove activity!\n";

        } else if (std::strcmp(command, "retrieve") == 0) {
            char retrieve_key[MAX_BYTE];
            std::cout << "Enter the name of the activity to search for: ";
            std::cin.get(retrieve_key, MAX_BYTE, '\n');
            std::cin.ignore(BIG_NUMBER, '\n');

            Activity* activity = tree[retrieve_key]; // magic operator overloading

            if (activity)
                activity->display();
            else
                std::cout << "Unable to retrieve activity!\n";

        } else if (std::strcmp(command, "search") == 0 ) {
            char search_key[MAX_BYTE];
            std::cout << "Enter the name of the activity to search for: ";
            std::cin.get(search_key, MAX_BYTE, '\n');
            std::cin.ignore(BIG_NUMBER, '\n');

            tree.display(search_key);

        } else if (std::strcmp(command, "display_all") == 0) {
            std::cout << tree; // magic friendly operator overloading usage
        } else if (std::strcmp(command, "buy") == 0) {
            char buy_key[MAX_BYTE];
            std::cout << "Enter the name of the activity to purchase: ";
            std::cin.get(buy_key, MAX_BYTE, '\n');
            std::cin.ignore(BIG_NUMBER, '\n');

            bool to_go;
            std::cout << "Do you want to take it to go? (1/0): ";
            std::cin >> to_go;
            std::cin.ignore(BIG_NUMBER, '\n');
            
            if (to_go)
                tree.buy(buy_key, out_house, total);
            else
                tree.buy(buy_key, in_house, total);

        } else {
            std::cout << "Command not recognized!\n";
        }

        std::cout << "command: ";
        std::cin.get(command, MAX_BYTE, '\n');
        std::cin.ignore(BIG_NUMBER, '\n');
    }

    std::cout << "Here is your order list: \n\n";
    std::cout << "To go: \n\n";
    std::cout << out_house << "\n\n";

    std::cout << "For here: \n\n";
    std::cout << in_house << "\n\n";

    std::cout << "Total Price: " << total << '\n';

    return 0;
}
