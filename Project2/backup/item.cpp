#include <iostream>
#include <cstring>

#include "item.h"

// null initialize membetrs
Item::Item() : name(NULL), type(NULL), desc(NULL), price(0) {};

// delete dynamic information held by Item
Item::~Item() {
    delete[] this->name;
    delete[] this->type;
    delete[] this->desc;
}

// deep copy the given data into this item object
Item::Item(const char* name, const char* type, const char* desc, int price) {
    int nameLen = std::strlen(name);
    this->name = new char[nameLen + 1];
    std::strcpy(this->name, name);
    this->name[nameLen] = '\0';

    int typeLen = std::strlen(type);
    this->type = new char[typeLen + 1];
    std::strcpy(this->type, type);
    this->type[typeLen] = '\0';

    int descLen = std::strlen(desc);
    this->desc = new char[descLen + 1];
    std::strcpy(this->desc, desc);
    this->desc[descLen] = '\0';

    this->price = price;
}

// deep copy the data from the given item into this item object
Item::Item(const Item& from) {
    int nameLen = std::strlen(from.name);
    this->name = new char[nameLen + 1];
    std::strcpy(this->name, from.name);
    this->name[nameLen] = '\0';

    int typeLen = std::strlen(from.type);
    this->type = new char[typeLen + 1];
    std::strcpy(this->type, from.type);
    this->type[typeLen] = '\0';

    int descLen = std::strlen(from.desc);
    this->desc = new char[descLen + 1];
    std::strcpy(this->desc, from.desc);
    this->desc[descLen] = '\0';

    this->price = from.price;
}

// compare the name of the item to the given name
int Item::compare(const char* key) const {
    return std::strcmp(key, this->name);
}

// compare the type of the item to the given type
int Item::compare_type(const char* type) const {
    return std::strcmp(type, this->type);
}

// display the item type and type member
void Item::display_typeinfo() const {
    std::cout << "This is an Item of type: " << this->type << '\n';
}

// display the information this Item holds
void Item::display() const {
    this->display_typeinfo();
    std::cout << "Name: " << this->name << '\n';
    //std::cout << "Type: " << this->type << '\n';
    std::cout << "Description: " << this->desc << '\n';
    std::cout << "Price: " << this->price << "\n\n";
}

// read the given data into the Item
void Item::read() { 
    char name[MAX_BYTE];
    char type[MAX_BYTE];
    char desc[MAX_BYTE];
    int price;

    std::cout << "Enter the name of the item: ";
    std::cin.get(name, MAX_BYTE, '\n');
    std::cin.ignore(BIG_NUMBER, '\n');

    std::cout << "Enter the type of object: ";
    std::cin.get(type, MAX_BYTE, '\n');
    std::cin.ignore(BIG_NUMBER, '\n');

    std::cout << "Enter a description: ";
    std::cin.get(desc, MAX_BYTE, '\n');
    std::cin.ignore(BIG_NUMBER, '\n');

    std::cout << "Enter a price: ";
    std::cin >> price;
    std::cin.ignore(BIG_NUMBER, '\n');
    
    *this = Item(name, type, desc, price); // utilizes copy assignment operator
}

// deep copy the data from the given item into this object
Item& Item::operator=(const Item& from) {
    int nameLen = std::strlen(from.name);
    this->name = new char[nameLen + 1];
    std::strcpy(this->name, from.name);
    this->name[nameLen] = '\0';

    int typeLen = std::strlen(from.type);
    this->type = new char[typeLen + 1];
    std::strcpy(this->type, from.type);
    this->type[typeLen] = '\0';

    int descLen = std::strlen(from.desc);
    this->desc = new char[descLen + 1];
    std::strcpy(this->desc, from.desc);
    this->desc[descLen] = '\0';

    this->price = from.price;

    return *this;
}

// null initialize object
NewItem::NewItem() {}

// delete dynamic info held by object
NewItem::~NewItem() {}

// construct object with data passed in and supply base class information to the base class constructor
NewItem::NewItem(const char* name, const char* type, const char* desc, int price, bool box) : Item(name, type, desc, price), in_box(box) {}

// copy construct object with data passed in and supply base class information to the base class copy constructor
NewItem::NewItem(const NewItem& other) : Item(other), in_box(other.in_box) {}

// display the item type and the type member
void NewItem::display_typeinfo() const {
    std::cout << "This is a New Item of type: " << this->type << '\n';
}

// identify the type of item and display the contents
void NewItem::display() const {
    Item::display();

    if (this->in_box)
        std::cout << "This item is still in the box\n";
    else
        std::cout << "This item has been removed from the box\n";
}

// read the given data into the new item
void NewItem::read() {
    Item::read();

    bool in_box;
    std::cout << "Is the item still in the box? (1/0): ";
    std::cin >> in_box;
    std::cin.ignore(BIG_NUMBER, '\n');

    this->in_box = in_box;
}

// null initialize object
UsedItem::UsedItem() {}

// delete dynamic info held by object
UsedItem::~UsedItem() {}

// construct object with data passed in and supply base class information to the base class constructor
UsedItem::UsedItem(const char* name, const char* type, const char* desc, int price, int years_old) : Item(name, type, desc, price), age(years_old) {}

// copy construct object with data passed in and supply base class information to the base class copy constructor
UsedItem::UsedItem(const UsedItem& other) : Item(other), age(other.age) {}

// display the item type and type member
void UsedItem::display_typeinfo() const {
    std::cout << "This is a Used Item of type: " << this->type << '\n';
}

// identify the type of item and display the contents
void UsedItem::display() const {
    Item::display();

    std::cout << "Age (years): " << this->age << '\n';
}

void UsedItem::read() {
    Item::read();

    int age;
    std::cout << "How old is this item? (years): ";
    std::cin >> age;
    std::cin.ignore(BIG_NUMBER, '\n');

    this->age = age;
}

// null initialize object
Electronic::Electronic() {}

// delete dynamic info held by object
Electronic::~Electronic() {}

// construct object with data passed in and supply base class information to the base class constructor
Electronic::Electronic(const char* name, const char* type, const char* desc, int price, bool is_used, bool works) : Item(name, type, desc, price), used(is_used), is_functioning(works) {}

// copy construct object with data passed in and supply base class information to the base class copy constructor
Electronic::Electronic(const Electronic& other) : Item(other), used(other.used), is_functioning(other.is_functioning) {}

// display the item type and type member
void Electronic::display_typeinfo() const {
    std::cout << "This is a ";
    if (this->used)
        std::cout << "Used";
    else
        std::cout << "New";

    std::cout << " Electronic of type: " << this->type << '\n';
}

// identify the type of item and display the contents and whether or not the electronic is used
void Electronic::display() const {
    Item::display();

    if (this->is_functioning)
        std::cout << "This electronic is functional\n";
    else
        std::cout << "This electronic is broken\n";
}

void Electronic::read() {
    Item::read();

    int used;
    std::cout << "Is the electronic used? (1/0): ";
    std::cin >> used;
    std::cin.ignore(BIG_NUMBER, '\n');

    int works;
    std::cout << "Does the electronic function? (1/0): ";
    std::cin >> works;
    std::cin.ignore(BIG_NUMBER, '\n');

    this->used = used;
    this->is_functioning = works;
}
