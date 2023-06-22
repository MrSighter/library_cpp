//
// Created by aleks on 26.05.2023.
//
#include <iostream>
#include <vector>
#include "borrowRecords.h"


borrowRecords::borrowRecords(){
    borrowId=1;
}
borrowRecords::~borrowRecords()=default;

void borrowRecords::print(const std::vector<borrowData *> &borrowDataFiltered) {
    std::cout<<"List of given borrow data instances";
    for (auto &it: borrowDataFiltered) {
        tm date0 = {0};
        std::cout<<it->ID<<"\tbookID: "<<it->bookID<<"\tclientID: "<<it->clientID<<"\t";
        std::cout<<"borrowDate: "<<it->borrowDate.tm_mday<<"."<<it->borrowDate.tm_mon+1<<"."<<it->borrowDate.tm_year+1900;
        (!(it->dateReturned == date0) ? std::cout << "\treturnDate: " << it->dateReturned.tm_mday << "."<< it->dateReturned.tm_mon + 1 << "." << it->dateReturned.tm_year + 1900: std::cout) << std::endl;

    }
}

std::ostream& operator<<(std::ostream& os, borrowRecords& data) {
    os<<data.borrowInstances.size()<<"\n";
    for (auto &it:data.borrowInstances) {
        os<<it;
    }
    return os;
}

void borrowRecords::addBorrow( unsigned int bookId,unsigned int clientId, tm borrowDate, tm returnDate){
    borrowInstances.emplace_back(getID(), bookId, clientId,borrowDate, returnDate);
    ++borrowId;
}

unsigned int borrowRecords::getID() const {
    return borrowId;
}

void borrowRecords::print() {
    for (auto& it:borrowInstances) {
        tm date0 = {0};
        std::cout<<it.ID<<"\tbookID: "<<it.bookID<<"\tclientID: "<<it.clientID<<"\t";
        std::cout<<"borrowDate: "<<it.borrowDate.tm_mday<<"."<<it.borrowDate.tm_mon+1<<"."<<it.borrowDate.tm_year+1900;
        (!(it.dateReturned == date0) ? std::cout << "\treturnDate: " << it.dateReturned.tm_mday << "."<< it.dateReturned.tm_mon + 1 << "." << it.dateReturned.tm_year + 1900: std::cout) << std::endl;
    }

}

bool borrowRecords::match(const borrowData& borrowInstance)const{
    return true;
}

void
borrowRecords::addBorrow(unsigned int ID, unsigned int bookId, unsigned int clientId, tm borrowDate, tm returnDate) {
    borrowInstances.emplace_back(ID, bookId, clientId,borrowDate, returnDate);
}

void borrowRecords::removeBorrow(const borrowData &data) {
    borrowInstances.remove(data);
}

std::istream &operator>>(std::istream &is, borrowRecords &data) {
    int ID, size, bookID, clientID;
    std::string line;
    tm date1 = {0,0,0,0,0,0};
    tm date2 = {0,0,0,0,0,0};
    std::getline(is, line, '\n');
    size=stoi(line);
    data.borrowId+=size;
    for (int i = 0; i < size; ++i) {
        std::getline(is, line, '\t');
        ID=stoi(line);
        std::getline(is, line, '\t');
        bookID=stoi(line);
        std::getline(is, line, '\t');
        clientID=stoi(line);
        std::getline(is, line, '.');
        date1.tm_mday=stoi(line);
        std::getline(is, line, '.');
        date1.tm_mon=stoi(line)-1;
        std::getline(is, line, '\t');
        date1.tm_year=stoi(line)-1900;
        std::getline(is, line, '.');
        date2.tm_mday=stoi(line);
        std::getline(is, line, '.');
        date2.tm_mon=stoi(line)-1;
        std::getline(is, line, '\n');
        date2.tm_year=stoi(line)-1900;
        data.borrowInstances.emplace_back(ID, bookID, clientID, date1, date2);
    }
    return is;
}

int borrowRecords::size() const {
    return (int)borrowInstances.size();
}


template <>
const unsigned int& borrowRecords::getField<unsigned int>(const borrowData& borrowInstance, BorrowSearch field) {
    switch (field) {
        case BorrowSearch::ID:
            return borrowInstance.ID;
        case BorrowSearch::BookID:
            return borrowInstance.bookID;
        case BorrowSearch::ClientID:
            return borrowInstance.clientID;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}template <>
const int& borrowRecords::getField<int>(const borrowData& borrowInstance, BorrowSearch field) {
    switch (field) {
        case BorrowSearch::ID:
            return (int&)borrowInstance.ID;
        case BorrowSearch::BookID:
            return (int&)borrowInstance.bookID;
        case BorrowSearch::ClientID:
            return (int&)borrowInstance.clientID;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}
template <>
const unsigned int& borrowRecords::getField<const unsigned int>(const borrowData& borrowInstance, BorrowSearch field) {
    switch (field) {
        case BorrowSearch::ID:
            return borrowInstance.ID;
        case BorrowSearch::BookID:
            return borrowInstance.bookID;
        case BorrowSearch::ClientID:
            return borrowInstance.clientID;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}
template <>
const tm& borrowRecords::getField<const tm&>(const borrowData& borrowInstance, BorrowSearch field) {
    switch (field) {
        case BorrowSearch::BorrowDate:
            return borrowInstance.borrowDate;
        case BorrowSearch::ReturnDate:
            return borrowInstance.dateReturned;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}
