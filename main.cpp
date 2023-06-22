#include <cstring>
#include "library.h"
#include "errors.h"
using namespace std;
int main() {
    //filling in dates to use later in project
    int size;
    std::string testPrint, test;
    tm testDate = {0, 0, 0, 23, 2, 123};
    tm date1 = {0, 0, 0, 21, 1, 123};

    library lib;

    //reading from file. Please do note, that files must be in the same folder as project build!!!
    {
       lib.readFromFile();
       size=lib.getSize();
    }
    //trying to read from file to a non-empty library
    //the function will return error, which is checked after catch
    {
        try {
            lib.readFromFile();
        } catch (logic_error &e) {
            if (!strcmp(e.what(), "Read can only happen if no books or clients were created."))
                std::cerr << "Error in read from file function. Did not return error with incorrect call";
        }
    }
    //checking functions adding books and clients
    {
    //checking book addition
    {
        lib.addBook("how to program in c", "me");
        lib.addBook("how to program in c++", "some guy");
        lib.addBook("Eiti chronicles", "student unknown");
        if (3+size != lib.getSize()) std::cerr << "Error in adding books. Wrong amount of data added.";
    }

    //checking client addition
    {
        lib.addClient("test Client", 123456453);
        lib.addClient("Eugenio Arbaccio", 354876563);
        if (5+size != lib.getSize()) std::cerr << "Error in adding clients. Wrong amount of data added.";
    }
}

    //checking borrow and return functions
    {
        lib.borrow(6, 3, testDate);
        lib.borrow(7, 4, testDate);
        lib.returnBook(1, lib.getCurrentDate());
        lib.borrow(1, 3, lib.getCurrentDate());
        lib.returnClient(3,lib.getCurrentDate());
        if (8+size != lib.getSize()) std::cerr << "Error in borrow function. Wrong amount of data added.";
    }

    //checking save to file. Function saves to another files, for the sake of repeating tests with same results
    lib.saveToFile();

    //checking remove functions
    {
        lib.removeBook(2);
        lib.removeClient(5);
        if(lib.findBooks(BookSearch::Available, false).empty()) std::cerr<<"remove book did not remove any book.";
        if(lib.findBooks(BookSearch::Available, false).size()!=2) std::cerr<<"remove book did not remove any book.";
    }

    //checking find functions
    {
        if(lib.findBooks(BookSearch::ID, 5).front()->getID()!=5)std::cerr<<"Error in findBooks function. Did not search by ID correctly";
        if(lib.findBooks(BookSearch::Borrowed, true).size()!=1)std::cerr<<"Error in findBooks function. Did not search by borrowed correctly";
        test="c++";
        if(lib.findBooks(BookSearch::Title, test).size()!=3)std::cerr<<"Error in findBooks function. Did not search by title correctly";
        test="author";
        if(lib.findBooks(BookSearch::Author, test).size()!=1)std::cerr<<"Error in findBooks function. Did not search by author correctly";

        if(lib.findClients(ClientSearch::ID, 1).front()->getID()!=1)std::cerr<<"Error in findClients function. Did not search by ID correctly";
        if(lib.findClients(ClientSearch::PhoneNumber, 123456789).size()!=1)std::cerr<<"Error in findClients function. Did not search by phone Number correctly";
        if(lib.findClients(ClientSearch::BooksBorrowed, 3).size()!=1)std::cerr<<"Error in findClients function. Did not search by books borrowed correctly";
        if(lib.findClients(ClientSearch::Available, false).size()!=2)std::cerr<<"Error in findClients function. Did not search by available correctly";
        test="spack jarrow";
        if(lib.findClients(ClientSearch::Name, test).size()!=1)std::cerr<<"Error in findClients function. Did not search by name correctly";
    }

    //a few incorrect cases
    {
        try {
            lib.borrow(2, 6, lib.getCurrentDate());
        } catch (logic_error& e) {
            if(std::strcmp("Book not available. Borrow unsuccessful.",e.what())!=0) std::cerr<<"error in error handling of borrow. Did not return error when borrowing deleted book";
        }
        try {
            lib.returnBook(2, lib.getCurrentDate());
        } catch (logic_error& e) {
            if(std::strcmp("Book unavailable. Return unsuccessful.",e.what())!=0) std::cerr<<"error in error handling of return book. Did not return error when returning deleted book";
        }
        try {
            lib.returnClient(5, lib.getCurrentDate());
        } catch (logic_error& e) {
            if(std::strcmp("Error in returnClient function. Client of a given Id is not available.",e.what())!=0) std::cerr<<"error in error handling of return client. Did not return error when returning deleted client";
        }
        try {
            lib.returnBook(7, date1);
        } catch (logic_error& e) {
            if(std::strcmp("Error in returnBook. Provided returnDate is earlier that borrow date.",e.what())!=0) std::cerr<<"error in error handling of return client. Did not return error when returning deleted client";
        }
    }
    std::cout<<"All tests passed.";
    return 0;
}