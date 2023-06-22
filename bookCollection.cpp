//
// Created by aleks on 26.05.2023.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "bookCollection.h"
#include "searchFields.h"

bookCollection::bookCollection(){
    bookId=1;
}
bookCollection::~bookCollection()=default;

void bookCollection::print(){
    for (auto &it:bookList) {
        std::cout<<it.ID<<"\t"<<it.title<<"\t"<<it.author<<"\t";
        if(!it.available){
            std::cout<<"deleted"<<std::endl;
        }else std::cout << (it.borrowed ? "borrowed" : "not borrowed") << std::endl;
    }
}
void bookCollection::print(const std::vector<book*> &booksFiltered) {
    std::cout<<"list of given books"<<std::endl;
    for (auto &it: booksFiltered) {
        std::cout<<it->ID<<"\t"<<it->title<<"\t"<<it->author<<"\t";
        if(!it->available){
            std::cout<<"deleted"<<std::endl;
        }else std::cout << (it->borrowed ? "borrowed" : "not borrowed") << std::endl;
    }
}

void bookCollection::addBook(const std::string& title,const std::string& author){
    bookList.emplace_back(bookId, title, author);
    ++bookId;
}

std::ostream &operator<<(std::ostream &os, const bookCollection &data) {
    os<<data.bookList.size()<<"\n";
    for (auto&it:data.bookList) {
        os<<it;
    }
    return os;
}

std::istream &operator>>(std::istream &is, bookCollection &data) {
    int ID, size;
    std::string title, author, line;
    bool borrowed, available;
    std::getline(is, line, '\n');
    size = stoi(line);
    data.bookId+=size;
    for (int i = 0; i < size; ++i) {
        std::getline(is, line, '\t');
        ID = std::stoi(line);
        std::getline(is, line, '\t');
        title.assign(line);
        std::getline(is, line, '\t');
        author.assign(line);
        std::getline(is, line, '\t');
        borrowed = stoi(line);
        std::getline(is, line, '\n');
        available = stoi(line);
        data.bookList.emplace_back(ID, title, author, borrowed, available);
        data.bookId=size;
    }
    return is;
}

int bookCollection::size() const {
    return (int)bookList.size();
}

template<>
const unsigned int& bookCollection::getField<const unsigned int>(const book& book, BookSearch field) const {
    switch (field) {
        case BookSearch::ID:
            return book.ID;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}

template<>
const std::string& bookCollection::getField<std::string>(const book& book, BookSearch field) const {
    switch (field) {
        case BookSearch::Title:
            return book.title;
        case BookSearch::Author:
            return book.author;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}

template<>
const bool& bookCollection::getField<bool>(const book& book, BookSearch field) const {
    switch (field) {
        case BookSearch::Borrowed:
            return book.borrowed;
        case BookSearch::Available:
            return book.available;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}

// Specialization for unsigned int
template<>
const unsigned int& bookCollection::getField<unsigned int>(const book& book, BookSearch field) const {
    switch (field) {
        case BookSearch::ID:
            return book.ID;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}
template<>
const int& bookCollection::getField<int>(const book& book, BookSearch field) const {
    switch (field) {
        case BookSearch::ID:
            return (int&)book.ID;
        default:
            throw std::invalid_argument("Invalid search field.");
    }
}


