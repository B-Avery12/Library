// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <limits>
#include "DataStore.hpp"
#include <sqlite3.h>
#include <string.h>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <sstream>

std::string getBookTitle();
std::string getBookContentPath();
std::string getBookContent(std::string fileName);

static int callback(void* data, int argc, char** argv, char** azColName) 
{ 
    int i; 
    fprintf(stderr, "%s: ", (const char*)data); 
  
    for (i = 0; i < argc; i++) { 
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    } 
  
    printf("\n"); 
    return 0; 
}

int main()
{
    int functionOption;
    std::string title;
    std::string path;
    std::string content;
    bool successfulOperation;

    // Storage testing
    DataStore db = DataStore(); 
    if (!db.OpenConnection()) {
        std::cout << "Shutting down as we weren't able to connect to the datastore." << std::endl;
        std::cout << "Please enter any key to exit: ";
        std::cin >> functionOption;
        return -1;
    }

    if (!db.CreateTable()) {
        std::cout << "Shutting down as we weren't able to create correct table in datastore." << std::endl;
        std::cout << "Please enter any key to exit: ";
        std::cin >> functionOption;
        return -1;
    };

    std::cout << "Welcome to the Library!\n";
    
    while (true) {
        std::cout << "\nAt the library you can do 5 things:\n";
        std::cout << "1 - List all the books we have\n";
        std::cout << "2 - Add a new book to the librayr\n";
        std::cout << "3 - Update an existing book contents\n";
        std::cout << "4 - Read a specific book\n";
        std::cout << "5 - Delete a specific book\n";
        std::cout << "6 - Exit the library\n";
        std::cout << "Please enter the number of the action you would like to take and then hit enter\n";
        std::cin >> functionOption;
        std::cin.ignore();

        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Unrecgonized input please input a number 1 - 5\n";
            continue;
        }

        switch (functionOption) 
        {
        case 1:
            std::cout << "Listing all books:\n";
            db.ReadBooks();
            break;
        case 2:
            std::cout << "Adding a new book:\n";
            title = getBookTitle();
            path = getBookContentPath();
            content = getBookContent(path);
            if (!db.CreateBook(title, content)) {
                std::cout << "Book wasn't saved\n";
            }
            break;
        case 3:
            std::cout << "Updating existing book:\n";
            title = getBookTitle();
            path = getBookContentPath();
            content = getBookContent(path);
            if (!db.UpdateBook(title, content)) {
                std::cout << "Book wasn't updated\n";
            }
            // successfulOperation = lib.UpdateBook(title, path);
            break;
        case 4:
            std::cout << "Reading a book:\n";
            title = getBookTitle();
            db.ReadBook(title);
            break;
        case 5:
            std::cout << "Deleting a specific book:\n";
            title = getBookTitle();
            db.DeleteBook(title);
            // successfulOperation = lib.DeleteBook(title);
            break;
        case 6:
            db.CloseConnection();
            return 0;
        default:
            std::cout << "I'm sorry " << functionOption << " isn't a valid function currently. Please enter a number between 1 and 5\n";
        }
    }
}

std::string getBookTitle() {
    std::string title;
    std::cout << "Please enter the title for the book:\n";
    std::getline(std::cin, title);
    return title;
}

std::string getBookContentPath() {
    std::string path;
    std::cout << "Please enter txt file name (Note: The file needs to be in the same directory as this library):\n";
    std::getline(std::cin, path);
    return path;
}

std::string getBookContent(std::string fileName) {
    std::ostringstream sstr;
    std::ifstream file(fileName);
    if (file){
        sstr << file.rdbuf();
        return sstr.str();
    } else {
        std::cerr << "Book not created because the file could not be opened!\n"; // Report error
        std::cerr << "Error code: " << std::strerror(errno); // Get some info as to why
        return "";
    }
}
