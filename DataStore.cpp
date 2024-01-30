#include "DataStore.hpp"
#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include <format>

DataStore::DataStore() {
    DBName = "LibraryStore.db";
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
                        "TITLE    TEXT    PRIMARY KEY    NOT NULL, "
                        "CONTENT  TEXT                   NOT NULL);"; 
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
    sqlite3_stmt *compiledStatement;
    std::string sql = "INSERT INTO LIBRARY VALUES(?1, ?2);";
    int resultCode = sqlite3_prepare_v2(DB, sql.c_str(), -1, &compiledStatement, NULL);
    if (resultCode != SQLITE_OK) {
        std::cerr << "Error adding book: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    resultCode = sqlite3_bind_text(compiledStatement, 1, title.c_str(), -1, NULL);
    if (resultCode != SQLITE_OK) {
        std::cerr << "Error adding book during title bind: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    resultCode = sqlite3_bind_text(compiledStatement, 2, content.c_str(), -1, NULL);
    if (resultCode != SQLITE_OK) {
        std::cerr << "Error adding book during content bind: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    resultCode = sqlite3_step(compiledStatement);
    if (resultCode == SQLITE_ROW) {
        int textColumn = 1;
        std::cout << sqlite3_column_text(compiledStatement, textColumn);
    } else if (resultCode != SQLITE_DONE) {
        std::cerr << "Error adding book druing step: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);

        return false;
    }

    sqlite3_finalize(compiledStatement);

    return true;
}

bool DataStore::ReadBooks() {
    char* messaggeError;
    std::string query = "SELECT * FROM LIBRARY;"; 
    int exit = sqlite3_exec(DB, query.c_str(), titleCallBack, NULL, &messaggeError);
    if (exit != SQLITE_OK) { 
        std::cerr << "Error READING book titles: " << messaggeError << std::endl;
        sqlite3_free(messaggeError);
        return false;
    }
    return true;
}

bool DataStore::UpdateBook(std::string title, std::string content) {
    sqlite3_stmt *compiledStatement;
    std::string sql = "UPDATE LIBRARY SET CONTENT = ?1 WHERE TITLE = ?2;";
    int resultCode = sqlite3_prepare_v2(DB, sql.c_str(), -1, &compiledStatement, NULL);
    if (resultCode != SQLITE_OK) {
        std::cerr << "Error updating book: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    resultCode = sqlite3_bind_text(compiledStatement, 1, content.c_str(), -1, NULL);
    if (resultCode != SQLITE_OK) {
        std::cerr << "Error updating book during content bind: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    resultCode = sqlite3_bind_text(compiledStatement, 2, title.c_str(), -1, NULL);
    if (resultCode != SQLITE_OK) {
        std::cerr << "Error updating book during title bind: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    resultCode = sqlite3_step(compiledStatement);
    if (resultCode == SQLITE_ROW) {
        int textColumn = 1;
        std::cout << sqlite3_column_text(compiledStatement, textColumn);
    } else if (resultCode != SQLITE_DONE) {
        std::cerr << "Error updating book druing step: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);

        return false;
    }

    sqlite3_finalize(compiledStatement);

    return true;
}

bool DataStore::DeleteBook(std::string title) {
    sqlite3_stmt *compiledStatement;
    std::string sql = "DELETE FROM LIBRARY WHERE TITLE = ?1;";
    int resultCode = sqlite3_prepare_v2(DB, sql.c_str(), -1, &compiledStatement, NULL);
    if (resultCode != SQLITE_OK) {
        std::cerr << "Error Deleting book: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    resultCode = sqlite3_bind_text(compiledStatement, 1, title.c_str(), -1, NULL);
    if (resultCode != SQLITE_OK) {
        std::cerr << "Error deleting book during title bind: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    resultCode = sqlite3_step(compiledStatement);
    if (resultCode != SQLITE_DONE) {
        std::cerr << "Error deleting book during step: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    sqlite3_finalize(compiledStatement);

    return true;
}

bool DataStore::ReadBook(std::string title) {
    sqlite3_stmt *compiledStatement;
    std::string sql = "SELECT * FROM LIBRARY WHERE TITLE=?1;";
    int resultCode = sqlite3_prepare_v2(DB, sql.c_str(), -1, &compiledStatement, NULL);
    if (resultCode != SQLITE_OK) {
        std::cerr << "Error reading book: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    resultCode = sqlite3_bind_text(compiledStatement, 1, title.c_str(), -1, NULL);
    if (resultCode != SQLITE_OK) {
        std::cerr << "Error reading book during title bind: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);
        return false;
    }

    resultCode = sqlite3_step(compiledStatement);
    if (resultCode == SQLITE_ROW) {
        int textColumn = 1;
        std::cout << sqlite3_column_text(compiledStatement, textColumn);
    } else if (resultCode != SQLITE_DONE) {
        std::cerr << "Error reading book during step: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(compiledStatement);

        return false;
    }

    sqlite3_finalize(compiledStatement);

    return true;
}

int DataStore::titleCallBack(void* data, int argc, char** argv, char** azColName) 
{ 
    for (int i = 0; i < argc; i++) {
        if (strcmp(azColName[i], "TITLE") == 0) {
            printf("%s\n", argv[i]);
        }
    } 
  
    return 0; 
}