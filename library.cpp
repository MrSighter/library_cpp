#include <algorithm>
#include <fstream>
#include "library.h"
#include "searchFields.h"
#include "errors.h"


//library functions
library::library(int maxBorrows, float dailyAmount, float maxOverdue){
    maxBorrow=maxBorrows;
    library::dailyOverdue=dailyAmount;
    overdueBlock=maxOverdue;
    library::currentDate={0,0,0,24,04,123};
}
library::~library()=default;

unsigned int library::getMaxBorrow() const {
    return maxBorrow;
}
float library::getDailyOverdue() const {
    return dailyOverdue;
}
float library::getOverdueBlock() const {
    return overdueBlock;
}
tm library::getCurrentDate() {
    return currentDate;
}

 bool library::canBorrow(client& client) const{
    return client.getBorrowedNumber()<library::getMaxBorrow();
}
 float library::calculateOverdue(tm borrowDate, tm returnDate) const {
    float overdue=((((float)(mktime(&returnDate)- mktime(&borrowDate)-30*24*60*60)/60/60/24)))*getDailyOverdue();
    if(overdue>0) return overdue;
    return 0;
}

void library::setMaxBorrow(int borrowMax) {
    if(borrowMax<=0) throw std::invalid_argument("Incorrect value. Maximum number of borrowed books must be more than 0.");
    else maxBorrow=borrowMax;
}
void library::setDailyOverdue(float value) {
    if(value<=0) throw std::invalid_argument("Incorrect value. Daily overdue must be more than 0.");
    else dailyOverdue=value;
}
void library::setOverdueBlock(float value) {
    if(value<=0) throw std::invalid_argument("Incorrect value. Overdue block must be more than 0.");
    else overdueBlock=value;
}
void library::setCurrentDate(unsigned int day,unsigned  int month,unsigned int yearAfter1900) {
    currentDate={0,0,0,(int)day,(int)month,(int)yearAfter1900};
}

void library::print() {
    std::cout << "Contents of the library:" << std::endl;
    std::cout << "Books:" << std::endl;
    books.print();
    std::cout << std::endl;
    std::cout << "Clients:" << std::endl;
    clients.print();
    std::cout << std::endl;
    std::cout << "Borrows:" << std::endl;
    borrows.print();
    std::cout << std::endl;
    std::cout << "History:" << std::endl;
    history.print();
    std::cout << std::endl;

    }

void library::borrow(unsigned int bookId, unsigned int clientId, tm borrowDate) {
    std::vector<book*> checkBook = books.findBooks(BookSearch::ID,bookId);
    if(checkBook.empty()){
        throw InvalidID("Book of a given ID does not exist: ", (int)bookId);
    }
    if(checkBook.size()>1){
        static_assert("There are more than one book of a given ID");
    }
    if(checkBook.front()->borrowed==1){
        throw std::logic_error("Book already borrowed. Borrow unsuccessful.");
    }
    if(checkBook.front()->available!=1){
        throw std::logic_error("Book not available. Borrow unsuccessful.");
    }
    std::vector<client*> checkClient = clients.findClient(ClientSearch::ID, clientId);
    if(checkClient.empty()){
        throw InvalidID("Client of a given ID does not exist: ", (int)clientId);
    }
    if(checkClient.size()>1){
        static_assert("There are more than one client of a given ID");
    }
    if(checkClient.front()->booksBorrowed>=maxBorrow){
        throw MaxReached("Client has borrowed too many books: ", (int)checkClient.front()->booksBorrowed, ". Maximum borrows allowed: ", (int)maxBorrow);
    }
    if(checkClient.front()->overdue>=overdueBlock){
        throw MaxReached("Client has reached maximum overdue: ", (int)checkClient.front()->overdue, ". Maximum overdue allowed: ", (int)overdueBlock);
    }
    checkBook.front()->setBorrowed(true);
    checkClient.front()->setBorrowed(1);
    borrows.addBorrow(bookId,clientId,borrowDate);
}

void library::addBook(const std::string &title, const std::string &author) {
books.addBook(title, author);
}

void library::addClient(const std::string &name, unsigned int phoneNumber) {
clients.addClient(name, phoneNumber);
}

void library::returnBook(unsigned int bookId, tm returnDate){
    std::vector<book*> foundBooks = books.findBooks(BookSearch::ID, bookId);
    if(foundBooks.empty()){
        throw InvalidID("Book of a given ID does not exist: ", (int)bookId);
    }
    if(foundBooks.size()>1){
        throw InvalidID("There are two books with the same ID: ", (int)bookId);
    }
    if(!foundBooks.front()->available){
        throw std::logic_error("Book unavailable. Return unsuccessful.");
    }
    if(!foundBooks.front()->borrowed){
        throw std::logic_error("Book not borrowed. ReturnBook unsuccessful.");
    }
    std::vector<borrowData*> foundBorrows= borrows.findBorrowed(BorrowSearch::BookID, static_cast<unsigned int>(bookId));
    if(foundBorrows.empty()){
        throw InvalidID("Borrow of a given bookID does not exist: ", (int)bookId);
    }
    if(foundBorrows.size()>1){
        static_assert("There are more than one borrow of a given bookID");
    }
    if(mktime(&foundBorrows.front()->borrowDate)> mktime(&returnDate)){
        throw std::invalid_argument("Error in returnBook. Provided returnDate is earlier that borrow date.");
    }
    std::vector<client*> foundClients = clients.findClient(ClientSearch::ID, foundBorrows.front()->clientID);
    foundBooks.front()->setBorrowed(false);
    foundClients.front()->setBorrowed(-1);
    foundClients.front()->setOverdue(calculateOverdue(foundBorrows.front()->borrowDate,returnDate));
    history.addBorrow(bookId,foundBorrows.front()->clientID,foundBorrows.front()->borrowDate, returnDate);
    borrows.removeBorrow(*foundBorrows.front());
}

void library::returnClient(unsigned int clientId, tm returnDate) {
    std::vector<client*> foundClients = clients.findClient(ClientSearch::ID, clientId);
    if(foundClients.empty()){
        throw InvalidID("Client of a given ID does not exist: ", (int)clientId);
    }
    if(foundClients.size()>1){
        static_assert("There are more than one client of a given ID");
    }
    if(!foundClients.front()->available){
        throw std::invalid_argument("Error in returnClient function. Client of a given Id is not available.");
    }
    std::vector<borrowData*> foundBorrows = borrows.findBorrowed(BorrowSearch::ClientID, static_cast<unsigned int>(clientId));
    std::vector<book*> foundBooks;
    for (auto& it:foundBorrows) {
        foundBooks.insert(foundBooks.end(),books.findBooks(BookSearch::ID, it->bookID).front());
    }
    if(foundBooks.size()!=foundBorrows.size()&&foundClients.front()->booksBorrowed!=foundBooks.size()){
        throw std::runtime_error("Error in returnClient. Different number of borrow instances and client's borrows");
    }
    for (auto it:foundBorrows) {
        it->setReturnDate(returnDate);
        foundClients.front()->setBorrowed(-1);
        foundClients.front()->setOverdue(calculateOverdue(it->borrowDate, returnDate));
        history.addBorrow(it->bookID,it->clientID,it->borrowDate,returnDate);
        borrows.removeBorrow(*it);
    }
    for (auto it:foundBooks){
        it->setBorrowed(false);
    }
}

void library::removeBook(unsigned int Id) {
std::vector<book*> foundBooks= books.findBooks(BookSearch::ID, Id);
    if(foundBooks.empty()){
        throw InvalidID("Error in removeBook function. No book of a given Id exists: ", (int)Id);
    }
    if(foundBooks.size()>1){
        static_assert("There are more than one book of a given Id.");
    }
    if(!foundBooks.front()->available){
        throw std::logic_error("Error in removeBook function. Book already removed.");
    }
    if(foundBooks.front()->borrowed){
        throw std::logic_error("error in removeBook function. Book is borrowed.");
    }
    foundBooks.front()->setAvailable(false);
}

void library::removeClient(unsigned int Id) {
    std::vector<client*> foundClients = clients.findClient(ClientSearch::ID, Id);
    if(foundClients.empty()){
        throw InvalidID("Error in removeClient function. No client of a given Id exists: ", (int)Id);
    }
    if(foundClients.size()>1){
        static_assert("There are more than one client of a given Id.");
    }
    if(!foundClients.front()->available){
        throw std::logic_error("Error in removeClient function. Client already removed.");
    }
    if(foundClients.front()->booksBorrowed>0){
        throw std::logic_error("Error in removeClient. Client has borrowed books.");
    }
    if(foundClients.front()->overdue>0.0){
        throw std::logic_error("Error in removeClient. Client has unpaid overdue.");
    }
    foundClients.front()->setAvailable(false);
}

void library::saveToFile() {
    std::ofstream BOOKS("books1.txt");
    BOOKS<<books;
    BOOKS.close();
    std::ofstream CLIENTS("clients1.txt");
    CLIENTS<<clients;
    CLIENTS.close();
    std::ofstream BORROWS("borrows1.txt");
    BORROWS<<borrows;
    CLIENTS.close();
    std::ofstream HISTORY("history1.txt");
    HISTORY<<history;
    HISTORY.close();
}

void library::readFromFile() {
    if(books.size() != 0&&clients.size()!=0){
        throw std::logic_error("Read can only happen if no books or clients were created");
    }
    std::ifstream BOOKS("books.txt");
    BOOKS>>books;
    BOOKS.close();
    std::ifstream CLIENTS("clients.txt");
    CLIENTS>>clients;
    CLIENTS.close();
    std::ifstream BORROWS("borrows.txt");
    BORROWS>>borrows;
    CLIENTS.close();
    std::ifstream HISTORY("history.txt");
    HISTORY>>history;
    HISTORY.close();
}
int library::getSize()const{
    return books.size()+clients.size()+borrows.size()+history.size();
}




