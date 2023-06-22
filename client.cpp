//
// Created by aleks on 26.05.2023.
//

#include <iostream>
#include "client.h"

client::client(unsigned int Id, const std::string& Name, unsigned int PhoneNumber, unsigned int BooksBorrowed, float Overdue, bool Available) {
    this->name.assign(Name);
    this->phoneNumber=PhoneNumber;
    ID=Id;
    booksBorrowed=BooksBorrowed;
    overdue=Overdue;
    available= Available;
}
client::~client() {
    name.clear();
}

unsigned int client::getID() const {
    return ID;
}
unsigned int client::getPhoneNumber() const {
    return phoneNumber;
}
std::string client::getName() const {
    return name;
}
unsigned int client::getBorrowedNumber() const {
    return booksBorrowed;
}
float client::getOverdue() const {
    return overdue;
}

void client::setOverdue(float val) {
    overdue+=val;
    if(overdue<0.0) overdue=0;
}
void client::setBorrowed(int val) {
    booksBorrowed+=val;
    if(booksBorrowed<0){
        std::cerr<<ID<<"client's booksBorrowed is less than 0 ("<<booksBorrowed<<")"<<std::endl;
        std::cerr<<"reverting to original booksBorrowed"<<std::endl;
        booksBorrowed+=abs(val);
    }
}

bool client::operator==(const client &other) const {
    return ID==other.ID;
}

std::ostream &operator<<(std::ostream &os, const client &data) {
    os<<data.ID<<"\t"<<data.name<<"\t"<<data.phoneNumber<<"\t"<<data.booksBorrowed<<"\t"<<data.overdue<<"\t"<<data.available<<std::endl;
    return os;
}

void client::setAvailable(bool val) {
 available=val;
}

std::istream& operator>>(std::istream& is, client& obj) {
    is >> obj.ID >> obj.name >> obj.phoneNumber>> obj.booksBorrowed >> obj.overdue >> std::boolalpha >> obj.available;
    return is;
}
