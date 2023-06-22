//
// Created by aleks on 26.05.2023.
//

#include <iostream>
#include "book.h"

book::book(unsigned int Id, const std::string& sourceTitle, const std::string& sourceAuthor,bool Borrowed,bool Available){
    ID=Id;
    title.assign(sourceTitle);
    author.assign(sourceAuthor);
    borrowed= Borrowed;
    available= Available;
}
book::book(unsigned int Id, const book &source){
    ID=Id;
    title.assign(source.title);
    author.assign(source.author);
    borrowed= false;
    available= true;
}
book::~book(){
    title.clear();
    author.clear();
}

unsigned int book::getID() const{
    return ID;
}
std::string book::getTitle() const{
    return title;
}
std::string book::getAuthor() const{
    return author;
}
bool book::getBorrowed() const {
    return borrowed;
}

void book::setBorrowed(bool value) {
    borrowed=value;
}
void book::setAvailable(bool value){
    available=value;
}

bool book::operator==(const book &other) const {
    return other.ID==ID;
}

std::ostream &operator<<(std::ostream &os, const book &data) {
    os<<data.ID<<"\t"<<data.title<<"\t"<<data.author<<"\t"<<data.borrowed<<"\t"<<data.available<<std::endl;
    return os;
}

bool book::getAvailable() const {
    return available;
}


