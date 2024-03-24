#include <iostream>
#include <cstring>

#include "item.h"
#include "list.h"
//#include "store.h" unneeded

int main() {
    DLL list;

    std::cout << "Welcome to the re-use store!\n";
    char command[MAX_BYTE];

    std::cout << "Commands: \n\tadd: add a new item\n\tremove: remove an item\n\tdisplay: display all items\n\tdisplay_old: display oldest most discounted items\n\tsearch: search items by type\n\tretrieve: display an item by name\n\tquit: exit the program\n";
    std::cout << "command: ";

    std::cin.get(command, MAX_BYTE, '\n');
    std::cin.ignore(BIG_NUMBER, '\n');

    while (std::strcmp(command, "quit") != 0) {
        if (std::strcmp(command, "add") == 0) {
            int option;
            std::cout << "What type of item to add? (1) New, (2) Used, (3) Electronic: ";
            std::cin >> option;
            std::cin.ignore(BIG_NUMBER, '\n');

            Item* item;
            if (option == 1) {
                item = new NewItem;
            } else if (option == 2) {
                item = new UsedItem;
            } else if (option == 3) {
                item = new Electronic;
            } else {
                std::cout << "\nOption not recognized!\n\n";
                continue; // the only way I could think of to skip adding the item without exiting the loop
            }

            item->read();
            list.add(*item);

            delete item;

        } else if (std::strcmp(command, "remove") == 0) {
            char remove_key[MAX_BYTE];
            std::cout << "Enter the name of the item to remove: ";
            std::cin.get(remove_key, MAX_BYTE, '\n');
            std::cin.ignore(BIG_NUMBER, '\n');

            if (!list.remove(remove_key))
                std::cout << "Unable to remove item!\n";

        } else if (std::strcmp(command, "display") == 0) {
            if (!list.display_all())
                std::cout << "Nothing to display!\n";

        } else if (std::strcmp(command, "display_old") == 0) {
            if (!list.display_old())
                std::cout << "Nothing to display!\n";

        } else if (std::strcmp(command, "search") == 0) {
            char type[MAX_BYTE];
            std::cout << "Enter the type of item to display: ";
            std::cin.get(type, MAX_BYTE, '\n');
            std::cin.ignore(BIG_NUMBER, '\n');

            if (!list.display_type(type))
                std::cout << "No items of that type found!\n";

        } else if (std::strcmp(command, "retrieve") == 0) {
            char search_key[MAX_BYTE];
            std::cout << "Enter the name of the item to display: ";
            std::cin.get(search_key, MAX_BYTE, '\n');
            std::cin.ignore(BIG_NUMBER, '\n');

            Item* item = list.retrieve(search_key);

            if (!item)
                std::cout << "Unable to retrieve item!\n";
            else
                item->display();

        } else {
            std::cout << "\nCommand not recognized!\n\n";
        }

        std::cout << "command: ";
        std::cin.get(command, MAX_BYTE, '\n');
        std::cin.ignore(BIG_NUMBER, '\n');
    }

    return 0;
}
