#ifndef DATASTORE_HPP
#define DATASTORE_HPP

#include <sqlite3.h>
#include <string>

class DataStore {
private:
    std::string TableExistsError;
    sqlite3* DB;
    std::string DBName;
    std::string CreateBookQuery;
    std::string UpdateBookQuery;
    std::string ReadBooksQuery;
    std::string DeleteBookQuery;
    static int titleCallBack(void* data, int argc, char** argv, char** azColName);
public:
    DataStore(); 
    ~DataStore();
    bool OpenConnection();
    void CloseConnection();
    bool CreateTable();
    bool CreateBook(std::string title, std::string content);
    bool ReadBooks();
    bool UpdateBook(std::string title, std::string content);
    bool DeleteBook(std::string title);
    bool ReadBook(std::string title);
};

#endif