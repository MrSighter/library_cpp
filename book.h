//
// Created by aleks on 26.05.2023.
//

#ifndef UNTITLED_BOOK_H
#define UNTITLED_BOOK_H
#include <string>
class book {
private:
    std::string title;  //title of a book
    std::string author; // author of a book
    unsigned int ID;    //unique identification number of a book
    bool borrowed;  //0 if a book is not borrowed, 1 if a book is borrowed
    bool available; //0 if a book was destroyed/deleted etc.

public:
    book(unsigned int Id, const std::string& sourceTitle, const std::string& sourceAuthor,bool Borrowed=false,bool Available=true);
    //creates a book with a given title and author
    //ID of a book is equal to bookID in the library with exception of loading from a file
    //after creating a book 1 is added to the bookID, to keep ID unique
    //borrowed is set to 0 (1 would mean that a book is borrowed)

    book(unsigned int Id, const book& source);
    //creates a book as a copy of another book
    //ID of a copy is not equal to source ID, ID has to be unique
    //ID of a copy is equal to bookID in the library
    //after creating a book 1 is added to the bookID, to keep the ID unique
    //copy's borrow is 0, even if the source book is already borrowed

    ~book();
    //deletes author and title strings

    [[nodiscard]] std::string getTitle() const;
    //returns title of a book

    [[nodiscard]] std::string getAuthor() const;
    //returns author of a book

    [[nodiscard]] unsigned int getID() const;
    //returns ID of a book

    [[nodiscard]] bool getBorrowed() const;
    //returns borrow value of a book

    [[nodiscard]] bool getAvailable() const;

    void setBorrowed(bool value);
    //set the borrowed value of a book

    void setAvailable(bool value);
    //set the available value of a book

    bool operator==(const book& other) const;
    //operator is set to compare books
    //it compares them only by their ID

    friend std::ostream& operator<<(std::ostream& os, const book& data);
    //outputs book data in a following format
    //ID    title   author    borrowed    available

    friend class library;
    friend class bookCollection;
};
#endif //UNTITLED_BOOK_H
