//
// Created by aleks on 26.05.2023.
//

#include <iostream>
#include <iomanip>
#include "borrowData.h"

bool operator==(const tm& date1, const tm& date2){
    return (date1.tm_mday==date2.tm_mday&&date1.tm_mon==date2.tm_mon&&date1.tm_year==date2.tm_year);
}

borrowData::borrowData(unsigned int ID, unsigned int bookID, unsigned int clientID, tm borrowDate, tm returnDate) {
    this->bookID=bookID;
    this->clientID=clientID;
    this->ID=ID;
    this->borrowDate=borrowDate;
    this->dateReturned=returnDate;
}
borrowData::~borrowData() = default;

unsigned int borrowData::getID() const {
    return ID;
}
unsigned int borrowData::getBookID() const {
    return bookID;
}
unsigned int borrowData::getClientID() const {
    return clientID;
}
tm borrowData::getBorrowDate() const {
    return borrowDate;
}
tm borrowData::getReturnDate() const{
    return dateReturned;
}

void borrowData::setReturnDate(tm& date) {
    dateReturned=date;
}

bool borrowData::operator==(const borrowData &other) const {
    return ID==other.ID;
}
std::ostream &operator<<(std::ostream &os, const borrowData &data) {
    os<<data.ID<<"\t"<<data.bookID<<"\t"<<data.clientID<<"\t"<<data.borrowDate.tm_mday<<"."<<data.borrowDate.tm_mon+1<<"."<<data.borrowDate.tm_year+1900;
    os<<"\t"<<data.dateReturned.tm_mday<<"."<<data.dateReturned.tm_mon+1<<"."<<data.dateReturned.tm_year+1900;
    os<<std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, borrowData& obj) {
    std::string dateString;
    is >> obj.ID >> obj.bookID >> obj.clientID >> dateString;
    std::istringstream dateStream(dateString);
    dateStream >> std::get_time(&obj.borrowDate, "%d.%m.%Y");
    dateStream >> std::get_time(&obj.dateReturned, "%d.%m.%Y");
    return is;
}