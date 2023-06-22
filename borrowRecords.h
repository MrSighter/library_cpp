//
// Created by aleks on 26.05.2023.
//

#ifndef UNTITLED_BORROWRECORDS_H
#define UNTITLED_BORROWRECORDS_H

#include <string>
#include <vector>
#include <list>
#include "borrowData.h"
#include "searchFields.h"

class borrowRecords {
private:
    std::list<borrowData> borrowInstances;
    unsigned int borrowId;

    template <typename Field>
    const Field& getField(const borrowData& borrowInstance, BorrowSearch field);
    //returns parameter of a borrow instance
    //respective to a field passed in arguments

    [[nodiscard]] bool match(const borrowData& borrowInstance)const;
    //base case for recursive match call
    template <typename T, typename... Args>
    bool match(const borrowData& borrowInstance, BorrowSearch field, const T&& first, const Args&... args) {
        const auto& newField = getField<std::decay_t<decltype(first)>>(borrowInstance, field);

        if (typeid(first)==typeid(unsigned int)) {
            if (first == newField)
                return match(borrowInstance, std::forward<Args>(args)...);
        }
        if constexpr (std::is_same_v<T, tm>) {
            const auto& borrowDate = borrowInstance.borrowDate;
            if (field == BorrowSearch::BorrowDate) {
                if (borrowDate.tm_year == first.tm_year && borrowDate.tm_mon == first.tm_mon && borrowDate.tm_mday == first.tm_mday)
                    return match(borrowInstance, std::forward<Args>(args)...);
            }
            else if (field == BorrowSearch::ReturnDate) {
                const auto& returnDate = borrowInstance.dateReturned;
                if (returnDate.tm_year == first.tm_year && returnDate.tm_mon == first.tm_mon && returnDate.tm_mday == first.tm_mday)
                    return match(borrowInstance, std::forward<Args>(args)...);
            }
        }

        return false;
    }
    //matches a parameter of borrow instance with a respective field
    //returns itself recursively with the rest of arguments if match passes
public:
    borrowRecords();
    ~borrowRecords();
    friend std::ostream& operator<<(std::ostream& os, borrowRecords& data);
    //outputs books in bookList in a following format:
    //ID    bookID   clientID    dateBorrowed    dateReturned
    friend std::istream& operator>>(std::istream& is, borrowRecords& data);
    //creates borrow instances with data passed in the stream

    [[nodiscard]] int size() const;
    //returns size of borrowInstances

    void print();
    //prints list with pointers to borrow instances given by a vector in a following format:
    //ID    bookID    clientID   dateBorrowed    dateReturned

    static void print(const std::vector<borrowData*>& borrowDataFiltered);
    //prints list with pointers to borrow instances given by a vector in a following format:
    //ID    bookID    clientID   dateBorrowed dateReturned

    void removeBorrow(const borrowData& data);
    //removes certain borrow instance from borrowInstances list

    template <typename... Args>
    std::vector<borrowData*> findBorrowed(Args&&... args) {
        if(sizeof...(args) % 2 !=0) throw std::invalid_argument("Invalid number of arguments. Must provide search field and value pairs.");

        std::vector<borrowData*> borrowFiltered;

        for (auto& it : borrowInstances) {
            if (match(it, std::forward<Args>(args)...)) {
                borrowFiltered.push_back(const_cast<borrowData*>(&it));
            }
        }
        return borrowFiltered;
    }
    //returns a vector of pointers to borrows complying with parameters set in arguments
    //parameters have to be typed in a following format
    //field, value,...
    //where field is a parameter of a book (Ex. dateReturned or ID)

    void addBorrow(unsigned int bookId,unsigned int clientId, tm borrowDate, tm returnDate={0,0,0,0,0,0});
    //adds new borrow Instance to the back of borrowInstances list

    void addBorrow(unsigned int ID, unsigned int bookId,unsigned int clientId, tm borrowDate, tm returnDate={0,0,0,0,0,0});
    //adds new borrow Instance with a given ID to the back of borrowInstances list
    //used when loading borrows from a file
    [[nodiscard]] unsigned int getID() const;
    //returns ID assigning unique borrows
};

#endif //UNTITLED_BORROWRECORDS_H
