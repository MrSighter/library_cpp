//
// Created by aleks on 31.05.2023.
//

#ifndef UNTITLED_ERRORS_H
#define UNTITLED_ERRORS_H

#include <exception>
#include <string>
#include <utility>
#include <sstream>

class InvalidID : public std::exception {
public:
    InvalidID(std::string  message, int argumentValue)
            : errorMessage(std::move(message)), argument(argumentValue) {}

    [[nodiscard]] const char* what() const noexcept override {
        return errorMessage.c_str();
    }
private:
    std::string errorMessage;
    int argument;
};

class MaxReached : public std::exception {
public:
    MaxReached(std::string error, int booksBorrowed,std::string Allowed,  int maxBorrow)
            : error(std::move(error)), value(booksBorrowed), allowed(std::move(Allowed)),  max(maxBorrow) {}

    [[nodiscard]] const char* what() const noexcept override {
        return generateErrorMessage().c_str();
    }

private:
    int max;
    int value;
    std::string allowed;
    std::string error;
    [[nodiscard]] std::string generateErrorMessage() const {
        std::stringstream ss;
        ss << error << value << allowed << max;
        return ss.str();
    }

};
#endif //UNTITLED_ERRORS_H
