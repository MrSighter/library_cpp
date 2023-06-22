//
// Created by aleks on 26.05.2023.
//

#ifndef UNTITLED_CLIENT_H
#define UNTITLED_CLIENT_H
#include <string>

class client{
private:
    std::string name;   //name of a client
    unsigned int ID;    //unique identification number of a client
    unsigned int booksBorrowed;   //number of books borrowed, ranging from 0 to maximum set in library class
    float overdue;   //the amount of money owed to the library for returning the books late
    unsigned int phoneNumber;   //phone number of a client, stored as a measure of contacting a client
    bool available; //0 if a client was destroyed/deleted etc.
public:
    client(unsigned int Id, const std::string& Name, unsigned int PhoneNumber, unsigned int BooksBorrowed=0, float Overdue=0, bool Available=true);
    //creates a client with a given name and phone number
    //ID of a book is equal to clientID in the library
    //after creating a book 1 is added to the clientID, to keep ID unique
    //overduePayment and booksBorrowed are set to 0

    ~client();
    //deletes name string

    [[nodiscard]] std::string getName() const;
    //returns name of a client

    [[nodiscard]] unsigned int getID() const;
    //returns ID of a client

    [[nodiscard]] unsigned int getBorrowedNumber() const;
    //returns number of books borrowed by a client

    [[nodiscard]] float getOverdue() const;
    //returns overdue payment of a client

    [[nodiscard]] unsigned int getPhoneNumber() const;
    //returns phone number of a client

    void setBorrowed(int val);
    //add val to clients borrowedBooks
    //if booksBorrowed>0, or booksBorrowed<maxBorrowed
    // prints error, and sets to minimum or maximum respectively

    void setOverdue(float val);
    //sets the client's overduePayment to val,
    // 0 is given as a default, because most often clients would pay all of their overdue in one go

    void setAvailable(bool val);

    bool operator==(const client& other) const;
    //operator is set to compare clients
    //it compares them by their ID

    friend std::ostream& operator<<(std::ostream& os, const client& data);
    //outputs client data in a following format
    //ID    name    phoneNumber booksBorrowed   overdue

    friend std::istream& operator>>(std::istream& is, client& obj);
    //loads data into a client

    friend class library;
    friend class clientBase;
};
#endif //UNTITLED_CLIENT_H
