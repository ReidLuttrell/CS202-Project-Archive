// Reid Luttrell
// File Purpose: encapsulate and providing prototyping for the different types of items

const int MAX_BYTE = 256;
const int BIG_NUMBER = 10000;

// class item - the base item class, holds data and functionality intrinsic to all item types
class Item {
public:
    // default constructor null initializes the item
    Item();
    // constructs and loads the given information into the item
    Item(const char* name, const char* type, const char* desc, int price);
    // copy constructs the item from the given item
    Item(const Item& from);
    // deletes all dynamic information in the item
    virtual ~Item();

    // copy assigns an item given another item
    Item& operator=(const Item& from);
    // compare the given name to the items name
    // returns strcmp result
    int compare(const char* key) const;
    // compare the given type to the item's type
    // returns strcmp result
    int compare_type(const char* type) const;
    // display the type info of the item
    virtual void display_typeinfo() const;
    // display the data the item holds
    virtual void display() const; // could consider pure virtual
    // prompt data and read into item
    virtual void read();
protected:
    // the name of the item
    char* name;
    // the type of item
    char* type;
    // a description of the item
    char* desc;
    // the price of the item
    int price;
};

// class NewItem - a subset of item with altered functionality
class NewItem : public Item {
public:
    // deafult constructor null initializes the new item
    NewItem();
    // construct the item with the given information
    NewItem(const char* name, const char* type, const char* desc, int price, bool box);
    // copy construct thew NewItem with the given NewItem
    NewItem(const NewItem& other);
    // delete all dynamic information held by the NewItem
    ~NewItem();

    // display the item info of the new item
    virtual void display_typeinfo() const;
    // display the information of the NewItem
    virtual void display() const;
    // prompt data and store into item
    virtual void read();
protected:
    bool in_box;
};

// class UsedItem - a subset of item with altered functionality
class UsedItem : public Item {
public:
    // default constructor null initializes the used item
    UsedItem();
    // construct the used item with the given information
    UsedItem(const char* name, const char* type, const char* desc, int price, int years_old);
    //copy construct the used item with the given used item
    UsedItem(const UsedItem& other);
    // delete all dynamic information the used item holds
    ~UsedItem();

    // display the type info of the used item
    virtual void display_typeinfo() const;
    // display the data of the used item
    virtual void display() const;
    // prompt data and store into item
    virtual void read();
protected:
    int age;
};

// class Electronic - a subset of item with altered functionality and additional data
class Electronic : public Item {
public:
    // default constructor null iniitalizes the electronic
    Electronic();
    // constructs the electronic with the given information
    Electronic(const char* name, const char* type, const char* desc, int price, bool is_used, bool works);
    // copy constructs the Electronic with the given Electronic
    Electronic(const Electronic& other);
    // deletes all dynamic information held by the ELectronic
    ~Electronic();
   
    // display the type info of the electronic
    virtual void display_typeinfo() const;
    // display the data of the Electronic
    virtual void display() const;
    // prompt data and store into item
    virtual void read();
protected:
    // whether or not the electronic is used
    bool used;
    // whether or not the electronic works
    bool is_functioning;
};
