//
// Created by aleks on 26.05.2023.
//

#ifndef UNTITLED_CLIENTBASE_H
#define UNTITLED_CLIENTBASE_H

#include <string>
#include <vector>
#include <list>
#include "client.h"
#include "searchFields.h"

class clientBase{
private:
    std::list<client> clientList;
    unsigned int clientId;

    template<typename Field>
    const Field& getField(const client& client, ClientSearch field) const;
    //returns parameter of a client instance
    //respective to a field passed in arguments

    [[nodiscard]] bool match(const client& client) const {
        return true;
    }
    //base case for recursive call of match

    template<typename First,typename... Args>
    bool match(const client& client, ClientSearch field, First&& first, Args&&... args) const{
        const auto& fieldValue = getField<std::decay_t<decltype(first)>>(client, field);

        if constexpr (std::is_same_v<std::decay_t<decltype(fieldValue)>, std::string>) {
            std::string lowercaseFieldValue = fieldValue;
            std::string lowercaseFirst = first;

            std::transform(lowercaseFieldValue.begin(), lowercaseFieldValue.end(), lowercaseFieldValue.begin(), ::tolower);
            std::transform(lowercaseFirst.begin(), lowercaseFirst.end(), lowercaseFirst.begin(), ::tolower);

            if (lowercaseFieldValue.find(lowercaseFirst) != std::string::npos) {
                return match(client, std::forward<Args>(args)...);
            }
        }
        else {
            if (fieldValue == first) {
                return match(client, std::forward<Args>(args)...);
            }
        }

        return false;
    }
    //matches a parameter of client instance with a respective field
    //returns itself recursively with the rest of arguments if match passes
public:
    clientBase();
    ~clientBase();

    friend std::ostream& operator<<(std::ostream& os,  clientBase& data);
    //outputs clients in clientBase in a following format:
    //ID   name    phoneNumber    booksBorrowed    overdue    available

    friend std::istream& operator>>(std::istream& is, clientBase& data);
    //creates new clients from data present ina stream

    void addClient(const std::string& name, unsigned int phoneNumber);
    //adds a client to the end of the clientBase

    [[nodiscard]] int size() const;
    //returns size of clientBase

    void print();
    //prints clients with pointers to clients given by a vector in a following format:
    //ID    name    booksBorrowed    overduePayment phoneNumber

    static void print(const std::vector<client*>& clientsFiltered);
    //prints clients with pointers to clients given by a vector in a following format:
    //ID    name    booksBorrowed    overduePayment phoneNumber

    template<typename... Args>
    std::vector<client*> findClient(Args&&... args) const{
        if(sizeof...(args) % 2 !=0) throw std::invalid_argument("Invalid number of arguments. Must provide search field and value pairs.");

        std::vector<client*> foundClients;


        for (auto& data : clientList) {
            if (match(data, std::forward<Args>(args)...)) {
                foundClients.push_back(const_cast<client*>(&data));
            }
        }

        return foundClients;
    }
    //returns a vector of pointers to clients complying with parameters set in arguments
    //parameters have to be typed in a following format
    //field, value,...
    //where field is a parameter of a book (Ex. name or ID)
};
#endif //UNTITLED_CLIENTBASE_H
