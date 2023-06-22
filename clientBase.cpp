//
// Created by aleks on 26.05.2023.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "clientBase.h"


clientBase::clientBase(){
    clientId=1;
}
clientBase::~clientBase()=default;

std::ostream& operator<<(std::ostream& os, clientBase& data){
    os<<data.clientList.size()<<"\n";
    for (auto &it: data.clientList)
        os << it;

    return os;
}
std::istream& operator>>(std::istream& is, clientBase& data){
    int ID, phoneNumber, booksBorrowed, size;
    float overdue;
    std::string name, line;
    bool available;
    std::getline(is, line, '\n');
    size = stoi(line);
    data.clientId+=size;
    for (int i = 0; i < size; ++i) {
        std::getline(is, line, '\t');
        ID=stoi(line);
        std::getline(is, line, '\t');
        name.assign(line);
        std::getline(is, line, '\t');
        phoneNumber= std::stoi(line);
        std::getline(is, line, '\t');
        booksBorrowed = stoi(line);
        std::getline(is, line, '\t');
        overdue = std::stof(line);
        std::getline(is, line, '\n');
        available=stoi(line);
        data.clientList.emplace_back(ID, name, phoneNumber, booksBorrowed, overdue, available);
    }
    return is;
}

void clientBase::print(const std::vector<client *> &clientsFiltered) {
    std::cout<<"list of filtered clients"<<std::endl;
    for (auto &it: clientsFiltered) {
        std::cout<<it->ID<<"\t"<<it->name<<"\t"<<it->phoneNumber<<"\t";
        if(!it->available){
            std::cout<<"deleted"<<std::endl;
            continue;
        }
        std::cout<<"books: "<<it->booksBorrowed<<"\toverdue: "<<it->overdue<<std::endl;
    }
}

void clientBase::addClient(const std::string& name, unsigned int phoneNumber) {
    clientList.emplace_back(clientId, name, phoneNumber);
    ++clientId;
}

template<>
const unsigned int& clientBase::getField<unsigned int>(const client& client, ClientSearch field) const {
    switch (field) {
        case ClientSearch::ID:
            return client.ID;
        case ClientSearch::PhoneNumber:
            return client.phoneNumber;
        case ClientSearch::BooksBorrowed:
            return client.booksBorrowed;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}
template<>
const int& clientBase::getField<int>(const client& client, ClientSearch field) const {
    switch (field) {
        case ClientSearch::ID:
            return (int&)client.ID;
        case ClientSearch::PhoneNumber:
            return (int&)client.phoneNumber;
        case ClientSearch::BooksBorrowed:
            return (int&)client.booksBorrowed;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}
template<>
const bool& clientBase::getField<bool>(const client& client, ClientSearch field) const {
    switch (field) {
        case ClientSearch::Available:
            return client.available;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}
template<>
const std::string& clientBase::getField<std::string>(const client& client, ClientSearch field) const {
    switch (field) {
        case ClientSearch::Name:
            return client.name;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}
void clientBase::print() {
    for (auto& it:clientList) {
        std::cout<<it.ID<<"\t"<<it.name<<"\t"<<it.phoneNumber<<"\t";
        if(!it.available){
            std::cout<<"deleted"<<std::endl;
            continue;
        }
        std::cout<<"books: "<<it.booksBorrowed<<"\toverdue: "<<it.overdue<<std::endl;
    }
}

int clientBase::size() const {
    return (int)clientList.size();
}
