//
// Created by aleks on 26.05.2023.
//

#ifndef UNTITLED_BOOKCOLLECTION_H
#define UNTITLED_BOOKCOLLECTION_H

#include <string>
#include <vector>
#include <list>
#include "book.h"
#include "searchFields.h"

class bookCollection{
private:
    std::list<book> bookList;
    unsigned int bookId;

    [[nodiscard]] bool match(const book& book) const {
        return true;
    }
    //base case for recursive call of match

    template<typename First, typename... Args>
    bool match(const book& book, BookSearch field, First&& first, Args&&... args) const {
        const auto& fieldValue = getField <std::decay_t<decltype(first)>>(book, field);

        if constexpr (std::is_same_v<std::decay_t<decltype(fieldValue)>, std::string>) {
            const auto& fieldValueStr = static_cast<const std::string&>(fieldValue);
            const std::string& firstStr = first;

            std::string lowercaseFieldValue = fieldValueStr;
            std::string lowercaseFirst = firstStr;

            std::transform(lowercaseFieldValue.begin(), lowercaseFieldValue.end(), lowercaseFieldValue.begin(), ::tolower);
            std::transform(lowercaseFirst.begin(), lowercaseFirst.end(), lowercaseFirst.begin(), ::tolower);

            if (lowercaseFieldValue.find(lowercaseFirst) != std::string::npos) {
                return match(book, std::forward<Args>(args)...);
            }
        } else {
            if (fieldValue == first) {
                return match(book, std::forward<Args>(args)...);
            }
        }

        return false;
    }
    //matches a parameter of book instance with a respective field
    //returns itself recursively with the rest of arguments if match passes
    template<typename Field>
    const Field& getField(const book& book, BookSearch field) const;
    //returns parameter of a book instance
    //respective to a field passed in arguments
public:
    bookCollection();
    ~bookCollection();

    void addBook(const std::string& title, const std::string& author);
    void print();
    //outputs books in bookList in a following format:
    //ID    title   author    borrowed/available

    static void print(const std::vector<book*>& booksFiltered);
    //prints books with pointers to books given by a vector in a following format:
    //ID    title    author    borrowed

    [[nodiscard]] int size() const;
    //returns size of bookList

    template<typename... Args>
    std::vector<book*> findBooks(Args&&... args) const {
        if(sizeof...(args) % 2 !=0) throw std::invalid_argument("Invalid number of arguments. Must provide search field and value pairs.");

        std::vector<book*> foundBooks;

        for (const auto& book : bookList) {
            if (match(book, std::forward<Args>(args)...)) {
                foundBooks.push_back(const_cast<::book*>(&book));  // Using const_cast to remove constness
            }
        }

        return foundBooks;
    }
    //returns a vector of pointers to books complying with parameters set in arguments
    //parameters have to be typed in a following format
    //field, value,...
    //where field is a parameter of a book (Ex. title or ID)

    friend std::ostream &operator<<(std::ostream &os, const bookCollection &data);
    //outputs each book in a separate line
    friend std::istream &operator>>(std::istream &is, bookCollection &data);
    //reads book data from a file and creates books complying with that data
};


#endif //UNTITLED_BOOKCOLLECTION_H

