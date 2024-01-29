#include "Library.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <cstring>

Library::Library() {
}

Library::Library(std::map<std::string, std::string> incomingBooks) {
    books = incomingBooks;
}

Library::~Library() {
 // NEED TO HANDL MEMORY MANAGEMENT THIS ISN"T GO
}

void Library::ListBooks() {
    if (books.empty()) {
        std::cout << "Our library is empty at the moment. Please add some books, thank you!\n";
        return;
    }

    for (auto const& [key, val] : books)
    {
        std::cout << key << std::endl;
    }
}

void Library::ReadBook(std::string title) {
    if (books.find(title) != books.end()) {
        std::cout << "Found book: " << title << std::endl << books[title] << std::endl;
    } else {
        std::cout << "We don't have: " << title << ". Please add it before trying to read it.\n";
    }
}

bool Library::AddBook(std::string title, std::string fileName) {
    std::ostringstream sstr;
    std::ifstream file(fileName);
    if (file){
        sstr << file.rdbuf();
        sstr.str();
        books.insert({title,  sstr.str()});
        return true;
    } else {
        std::cerr << "Book not created because the file could not be opened!\n"; // Report error
        std::cerr << "Error code: " << std::strerror(errno); // Get some info as to why
        return false;
    }
}

bool Library::DeleteBook(std::string title) {
    if ( books.erase(title) == 0) {
        std::cout << "Unable to delete: " << title << ", because the book doesn't exist.\n";
        return false;
    } 
    return true;
}

bool Library::UpdateBook(std::string title, std::string path) {
    if (books.find(title) == books.end()) {
        std::cout << "We don't have: " << title << ". Please add it before trying to update it.\n";
        return false;
    }
    DeleteBook(title);
    return AddBook(title, path);
}

std::map<std::string, std::string> Library::getBooks() {
    return books;
}