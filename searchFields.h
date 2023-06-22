//
// Created by aleks on 27.05.2023.
//

#ifndef UNTITLED_SEARCHFIELDS_H
#define UNTITLED_SEARCHFIELDS_H

enum class BookSearch {
    ID,
    Title,
    Author,
    Borrowed,
    Available
};
enum class ClientSearch{
    ID,
    Name,
    PhoneNumber,
    BooksBorrowed,
    Overdue,
    Available
};
enum class BorrowSearch {
    ID,
    BookID,
    ClientID,
    BorrowDate,
    ReturnDate
};
#endif //UNTITLED_SEARCHFIELDS_H
