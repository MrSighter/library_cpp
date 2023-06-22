//
// Created by aleks on 26.05.2023.
//

#ifndef UNTITLED_BORROWDATA_H
#define UNTITLED_BORROWDATA_H

#include<string>
#include <optional>

bool operator==(const tm& date1, const tm& date2);
//operator checking if two dates are equal
//used in setting return date

class borrowData{
private:
    unsigned int ID;    //ID of borrowData
    unsigned int bookID;    //ID of a borrowed book
    unsigned int clientID;  //ID of borrowing client
    tm borrowDate{};  //a time struct storing borrow date
    tm dateReturned{};  //a time struct storing return date (it's set to 0 if a book hasn't been returned yet)
public:
    borrowData(unsigned int ID, unsigned int bookId, unsigned int clientId, tm borrowDate, tm returnDate = {0,0,0,0,0,0});
    //sets borrowData's bookID to bookID, clientID to clientID, and tm borrowDate to borrowDate
    //sets ID to borrowID, then adds 1 to borrowID
    //other variables are set to 0, because the book hasn't been returned yet

    ~borrowData();
    //destructor will be empty here

    [[nodiscard]] unsigned int getID() const;

    [[nodiscard]] unsigned int getBookID() const;
    //returns bookID

    [[nodiscard]] unsigned int getClientID() const;
    //returns clientID

    [[nodiscard]] tm getBorrowDate() const;
    //returns borrowDate

    [[nodiscard]] tm getReturnDate() const;
    //returns returnDate

    bool operator==(const borrowData& other) const;
    //operator is set to compare borrow instances
    //compares them by their ID

    void setReturnDate(tm& date);
    //sets returnDate to given values
    //values not given (minute, second, etc.) are set to 0
    //can't set date prior to borrowDate


    friend std::ostream& operator<<(std::ostream& os, const borrowData& data);
    //outputs book data in a following format
    //ID    bookID   titleID    dd.mm.yyyy(borrowed) dd.mm.yyyy(returned, 0 if not returned yet)

    friend std::istream& operator>>(std::istream& is, borrowData& obj);
    //operator loading data into a borrowData object

    friend class borrowRecords;
    friend class library;
};
#endif //UNTITLED_BORROWDATA_H
