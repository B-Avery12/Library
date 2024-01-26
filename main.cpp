// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <limits>
#include "Library.hpp"

std::string getBookTitle();
std::string getBookContentPath();

int main()
{
    Library lib = Library();

    // Now we need to conecct to the database :D

    int functionOption;
    std::string title;
    std::string path;

    std::cout << "Welcome to the Library!\n";
    
    while (true) {
        std::cout << "\nAt the library you can do 5 things:\n";
        std::cout << "1 - List all the books we have\n";
        std::cout << "2 - Add a new book to the librayr\n";
        std::cout << "3 - Update an existing book contents\n";
        std::cout << "4 - Read a specific book\n";
        std::cout << "5 - Delete a specific book\n";
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
            lib.ListBooks();
            break;
        case 2:
            std::cout << "Adding a new book:\n";
            title = getBookTitle();
            path = getBookContentPath();
            bool added = lib.AddBook(title, path);
            break;
        case 3:
            std::cout << "Updating existing book:\n";
            title = getBookTitle();
            path = getBookContentPath();
            bool updated = lib.UpdateBook(title, path);
            break;
        case 4:
            std::cout << "Reading a book:\n";
            title = getBookTitle();
            lib.ReadBook(title);
            break;
        case 5:
            std::cout << "Deleting a specific book:\n";
            title = getBookTitle();
            bool deeted = lib.DeleteBook(title);
            break;
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
