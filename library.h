#ifndef UNTITLED_LIBRARY_H
#define UNTITLED_LIBRARY_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include "bookCollection.h"
#include "clientBase.h"
#include "borrowRecords.h"

class library {
private:
    unsigned int maxBorrow; //maximum books a client can borrow simultaneously
    float dailyOverdue; //overdue amount for one day too long of keeping a book
    float overdueBlock; //maximum amount of overdue, after which a client cannot borrow a book
    tm currentDate{}; //time struct of current date in the library
    bookCollection books; //books in a library
    clientBase clients; //clientBase in a library
    borrowRecords borrows; //current borrows in a library
    borrowRecords history; //past borrows in a library
public:
    explicit library(int maxBorrows=3, float dailyAmount=0.3, float maxOverdue=5);
    //sets the maxBorrow, dailyOverdue and maxOverdue of a library
    ~library();
    //deletes all lists in a library

    [[nodiscard]]  unsigned int getMaxBorrow() const;
    //returns maxBorrow of the library

    [[nodiscard]] int getSize()const;

    void setMaxBorrow(int maxBorrow);
    //sets the maxBorrow of the library

    [[nodiscard]]  float getDailyOverdue() const;
    //returns daily overdue

    void setDailyOverdue(float value);
    //sets dailyOverdue to a given value

    [[nodiscard]]  float getOverdueBlock() const;
    //returns overdue block

    void setOverdueBlock(float value);
    //sets overdueBlock to a given value

    [[nodiscard]] tm getCurrentDate();
    //returns a time struct of a currentDate

    void setCurrentDate(unsigned int day,unsigned int month,unsigned int yearAfter1900);
    //sets currentDate to a given value

    [[nodiscard]] float calculateOverdue(tm borrowDate, tm returnDate) const;
    //returns a subtraction of return date and borrow date in days and multiplied by library's daily overdue
    //returns 0 if returnDate is not given

    bool canBorrow(client& client) const;
    //check if bookSBorrowed of a clint with a given ID is less than library's maxBorrow

    void borrow(unsigned int bookId, unsigned int clientId, tm borrowDate);
    //if a client of a given ID can borrow a book, and if the book of a given ID is not borrowed yet
    //and if client and book of a given ID exist
    //creates a borrow instance, and adds it to the booksBorrowed list
    //changes the book's borrowed value to true
    //changes the client's booksBorrowed value to be 1 more
    //returns pointer to borrow instance
    //or nullptr if it couldn't been created

    void returnBook(unsigned int bookId, tm returnDate);
    //if there exists a borrow instance in booksBorrowed with a given bookID
    //sets returnDate of said borrow instance to returnDate
    //moves that borrow instance from booksBorrowed to borrowedHistory
    //changes the book's borrowed value to false
    //changes the client's booksBorrowed value to be 1 fewer
    //calculates clientOverdue and adds it to overduePayment

    void returnClient(unsigned int clientId, tm returnDate);
    //if  borrow instances in booksBorrowed with a given clientID exist
    //sets returnDate of every client's borrow instance to returnDate
    //moves those borrow instances from booksBorrowed to borrowedHistory
    //changes the books' borrowed value to false
    //changes the client's booksBorrowed value to 0
    //calculates clientOverdue and adds it to overduePayment


    void addBook(const std::string& title, const std::string& author);
    //adds book with a given data
    //user is not able to set the ID of a book to ensure ID uniqueness
    void addClient(const std::string& name, unsigned int phoneNumber);
    //adds client with a given data
    //user is not able to set the ID of a client to ensure ID uniqueness

    void removeBook(unsigned int Id);
    //sets the deleted value of a book of a given ID to 1
    //canceled if book is borrowed

    void removeClient(unsigned int Id);
    //sets the deleted value of a client of a given ID to 1
    //cancelled if client has any books borrowed or unpaid overdue

    void print();
    //prints variables of the library in a following format:
    //maxBorrow    dailyOverdue    overdueBlock currentDate
    //then prints list of books in a following format:
    //ID    title    author    borrowed/not borrowed/deleted
    //then prints list of clients in a following format:
    //ID    name    phoneNumber    deleted/(booksBorrowed    overduePayment)
    //then prints list of borrowData in a following format:
    //ID    bookID    clientID   dateBorrowed
    //then prints list of borrowHistory in a following format:
    //ID    bookID    clientID   dateBorrowed dateReturned

    template<typename... Arg>
    std::vector<const book*> findBooks(Arg&&... arg){
        std::vector<const book*> vectConst;
        std::vector<book*> vect = books.findBooks(std::forward<Arg>(arg)...);
        for (const book* it:vect) {
            vectConst.push_back(it);
        }
        return vectConst;
    }
    //function passes its arguments into a findBooks function in books

    template<typename... Arg>
    std::vector<const client*> findClients(Arg&&... arg){
        std::vector<const client*> vectConst;
        std::vector<client*> vect =clients.findClient(std::forward<Arg>(arg)...);
        for (const client* it:vect) {
            vectConst.push_back(it);
        }
        return vectConst;
    }
    //function passes its arguments into a findClients function in clients

    void saveToFile();
    //saves contents of the library to text files

    void readFromFile();
    //loads contents of the library from text files
    //can only import data to an empty library
    //books/clients/borrows/history must be empty
};
#endif