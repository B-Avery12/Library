#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <map>
#include <string>

class Library
{
private:
    std::map<std::string, std::string> books;
public:
    Library();
    Library(std::map<std::string, std::string> incomingBooks);
    ~Library();
    void ListBooks();
    bool AddBook(std::string title, std::string path); // Return a success message on add successful or an error message on unsuccessful
    void ReadBook(std::string title);
    bool DeleteBook(std::string title); // Return a success message on delete successful or an error message on unsuccessful
    bool UpdateBook(std::string title, std::string path); // Return a success message on update successful or an error message on unsuccessful
    std::map<std::string, std::string> getBooks();
};

#endif