#include "DataStore.hpp"
#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include <format>

DataStore::DataStore() {
    TableExistsError = "";
    DBName = "LibraryStore"; // This might throw an error since we're using char*, not strin
    CreateBookQuery = "";
    UpdateBookQuery = "";
    ReadBooksQuery = "";
    DeleteBookQuery = "";
}

DataStore::~DataStore() {
}

bool DataStore::OpenConnection() {
    if (sqlite3_open(DBName.c_str(), &DB)) { 
        std::cerr << "Error opening DB " << sqlite3_errmsg(DB) << std::endl; 
        return false; 
    } 
    return true;
}

void DataStore::CloseConnection() {
    sqlite3_close(DB);
}

bool DataStore::CreateTable() {
    char* messaggeError;
    int exit = 0;
    std::string sql = "CREATE TABLE LIBRARY("
                      "TITLE TEXT PRIMARY KEY     NOT NULL, "
                      "CONTENT          TEXT     NOT NULL);"; 
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError); 

    if (exit != SQLITE_OK) { 
        if (strcmp(messaggeError, "table LIBRARY already exists") != 0) {
            std::cerr << "Error creating table: " << messaggeError << std::endl;
            sqlite3_free(messaggeError);
            return false;
        }
    } 
    return true;
}

bool DataStore::CreateBook(std::string title, std::string content) {
    char* messaggeError;
    int exit = 0;
    std::string query = std::format("INSERT INTO LIBRARY VALUES({}, {});", title, content);
    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) { 
        std::cerr << "Error creating book: " << messaggeError << std::endl;
        sqlite3_free(messaggeError);
        return false;
    } 
    return true;
}

bool DataStore::ReadBooks() {
    char* messaggeError;
    int exit = 0;
    std::string query = "";
    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) { 
        std::cerr << "Error creating book: " << messaggeError << std::endl;
        sqlite3_free(messaggeError);
        return false;
    } 
    return true;
}

bool DataStore::UpdateBook(std::string title, std::string content) {
    return true;
}

bool DataStore::DeleteBook(std::string title) {
     char* messaggeError;
    int exit = 0;
    std::string query = std::format("DELETE FROM LIBRARY WHERE TITLE = {};", title);
    exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) { 
        std::cerr << "Error creating book: " << messaggeError << std::endl;
        sqlite3_free(messaggeError);
        return false;
    } 
    return true;
}
